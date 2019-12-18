#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_transport_mw {size_t xlat_size; size_t buff_size; size_t alloc_size; int /*<<< orphan*/  dma_addr; } ;
struct ntb_transport_ctx {TYPE_1__* ndev; struct ntb_transport_mw* mw_vec; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_3__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PIDX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int ntb_alloc_mw_buffer (struct ntb_transport_mw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_free_mw (struct ntb_transport_ctx*,int) ; 
 int ntb_mw_get_align (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_mw_set_trans (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 size_t round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntb_set_mw(struct ntb_transport_ctx *nt, int num_mw,
		      resource_size_t size)
{
	struct ntb_transport_mw *mw = &nt->mw_vec[num_mw];
	struct pci_dev *pdev = nt->ndev->pdev;
	size_t xlat_size, buff_size;
	resource_size_t xlat_align;
	resource_size_t xlat_align_size;
	int rc;

	if (!size)
		return -EINVAL;

	rc = ntb_mw_get_align(nt->ndev, PIDX, num_mw, &xlat_align,
			      &xlat_align_size, NULL);
	if (rc)
		return rc;

	xlat_size = round_up(size, xlat_align_size);
	buff_size = round_up(size, xlat_align);

	/* No need to re-setup */
	if (mw->xlat_size == xlat_size)
		return 0;

	if (mw->buff_size)
		ntb_free_mw(nt, num_mw);

	/* Alloc memory for receiving data.  Must be aligned */
	mw->xlat_size = xlat_size;
	mw->buff_size = buff_size;
	mw->alloc_size = buff_size;

	rc = ntb_alloc_mw_buffer(mw, &pdev->dev, xlat_align);
	if (rc) {
		mw->alloc_size *= 2;
		rc = ntb_alloc_mw_buffer(mw, &pdev->dev, xlat_align);
		if (rc) {
			dev_err(&pdev->dev,
				"Unable to alloc aligned MW buff\n");
			mw->xlat_size = 0;
			mw->buff_size = 0;
			mw->alloc_size = 0;
			return rc;
		}
	}

	/* Notify HW the memory location of the receive buffer */
	rc = ntb_mw_set_trans(nt->ndev, PIDX, num_mw, mw->dma_addr,
			      mw->xlat_size);
	if (rc) {
		dev_err(&pdev->dev, "Unable to set mw%d translation", num_mw);
		ntb_free_mw(nt, num_mw);
		return -EIO;
	}

	return 0;
}
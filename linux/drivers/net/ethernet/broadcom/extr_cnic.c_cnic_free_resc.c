#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cnic_uio_dev {int uio_dev; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;
struct cnic_local {int /*<<< orphan*/  cid_tbl; int /*<<< orphan*/  fcoe_cid_tbl; int /*<<< orphan*/ * ctx_tbl; int /*<<< orphan*/ * iscsi_tbl; TYPE_2__ kcq1; TYPE_1__ kcq2; int /*<<< orphan*/  kwq_16_data_info; int /*<<< orphan*/  kwq_info; int /*<<< orphan*/  gbl_buf_info; scalar_t__ ctx_blks; int /*<<< orphan*/ * ctx_arr; struct cnic_uio_dev* udev; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cnic_free_uio_rings (struct cnic_uio_dev*) ; 
 int /*<<< orphan*/  cnic_free_context (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_free_dma (struct cnic_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_free_id_tbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_free_resc(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_uio_dev *udev = cp->udev;

	if (udev) {
		udev->dev = NULL;
		cp->udev = NULL;
		if (udev->uio_dev == -1)
			__cnic_free_uio_rings(udev);
	}

	cnic_free_context(dev);
	kfree(cp->ctx_arr);
	cp->ctx_arr = NULL;
	cp->ctx_blks = 0;

	cnic_free_dma(dev, &cp->gbl_buf_info);
	cnic_free_dma(dev, &cp->kwq_info);
	cnic_free_dma(dev, &cp->kwq_16_data_info);
	cnic_free_dma(dev, &cp->kcq2.dma);
	cnic_free_dma(dev, &cp->kcq1.dma);
	kfree(cp->iscsi_tbl);
	cp->iscsi_tbl = NULL;
	kfree(cp->ctx_tbl);
	cp->ctx_tbl = NULL;

	cnic_free_id_tbl(&cp->fcoe_cid_tbl);
	cnic_free_id_tbl(&cp->cid_tbl);
}
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
struct switchtec_ntb {int* direct_mw_to_bar; int /*<<< orphan*/  self_shared_dma; int /*<<< orphan*/  self_shared; TYPE_1__* stdev; int /*<<< orphan*/  peer_shared; int /*<<< orphan*/  self_partition; int /*<<< orphan*/  mmio_peer_ctrl; int /*<<< orphan*/  nr_rsvd_luts; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LUT_SIZE ; 
 int config_rsvd_lut_win (struct switchtec_ntb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iomap (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switchtec_ntb_init_shared (struct switchtec_ntb*) ; 

__attribute__((used)) static int switchtec_ntb_init_shared_mw(struct switchtec_ntb *sndev)
{
	int self_bar = sndev->direct_mw_to_bar[0];
	int rc;

	sndev->nr_rsvd_luts++;
	sndev->self_shared = dma_alloc_coherent(&sndev->stdev->pdev->dev,
						LUT_SIZE,
						&sndev->self_shared_dma,
						GFP_KERNEL);
	if (!sndev->self_shared) {
		dev_err(&sndev->stdev->dev,
			"unable to allocate memory for shared mw\n");
		return -ENOMEM;
	}

	switchtec_ntb_init_shared(sndev);

	rc = config_rsvd_lut_win(sndev, sndev->mmio_peer_ctrl, 0,
				 sndev->self_partition,
				 sndev->self_shared_dma);
	if (rc)
		goto unalloc_and_exit;

	sndev->peer_shared = pci_iomap(sndev->stdev->pdev, self_bar, LUT_SIZE);
	if (!sndev->peer_shared) {
		rc = -ENOMEM;
		goto unalloc_and_exit;
	}

	dev_dbg(&sndev->stdev->dev, "Shared MW Ready\n");
	return 0;

unalloc_and_exit:
	dma_free_coherent(&sndev->stdev->pdev->dev, LUT_SIZE,
			  sndev->self_shared, sndev->self_shared_dma);

	return rc;
}
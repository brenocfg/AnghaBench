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
struct scif_hw_dev {TYPE_1__* hw_ops; } ;
struct scif_dev {int /*<<< orphan*/  node; int /*<<< orphan*/ * cookie; struct scif_hw_dev* sdev; } ;
struct TYPE_4__ {int card_initiated_exit; int /*<<< orphan*/  misc_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_irq ) (struct scif_hw_dev*,int /*<<< orphan*/ *,struct scif_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_cleanup_qp (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_cleanup_rma_for_zombies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_destroy_intr_wq (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_destroy_p2p (struct scif_dev*) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scif_invalidate_ep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_send_acks (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_send_exit (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_zap_mmaps (int /*<<< orphan*/ ) ; 
 scalar_t__ scifdev_is_p2p (struct scif_dev*) ; 
 int /*<<< orphan*/  stub1 (struct scif_hw_dev*,int /*<<< orphan*/ *,struct scif_dev*) ; 

void scif_cleanup_scifdev(struct scif_dev *dev)
{
	struct scif_hw_dev *sdev = dev->sdev;

	if (!dev->sdev)
		return;
	if (scifdev_is_p2p(dev)) {
		if (dev->cookie) {
			sdev->hw_ops->free_irq(sdev, dev->cookie, dev);
			dev->cookie = NULL;
		}
		scif_destroy_intr_wq(dev);
	}
	flush_work(&scif_info.misc_work);
	scif_destroy_p2p(dev);
	scif_invalidate_ep(dev->node);
	scif_zap_mmaps(dev->node);
	scif_cleanup_rma_for_zombies(dev->node);
	flush_work(&scif_info.misc_work);
	scif_send_acks(dev);
	if (!dev->node && scif_info.card_initiated_exit) {
		/*
		 * Send an SCIF_EXIT message which is the last message from MIC
		 * to the Host and wait for a SCIF_EXIT_ACK
		 */
		scif_send_exit(dev);
		scif_info.card_initiated_exit = false;
	}
	scif_cleanup_qp(dev);
}
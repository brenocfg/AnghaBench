#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scif_hw_dev {TYPE_1__* hw_ops; } ;
struct scif_dev {int /*<<< orphan*/  intr_bh; int /*<<< orphan*/  intr_wq; int /*<<< orphan*/  db; struct scif_hw_dev* sdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack_interrupt ) (struct scif_hw_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scif_hw_dev*,int /*<<< orphan*/ ) ; 

irqreturn_t scif_intr_handler(int irq, void *data)
{
	struct scif_dev *scifdev = data;
	struct scif_hw_dev *sdev = scifdev->sdev;

	sdev->hw_ops->ack_interrupt(sdev, scifdev->db);
	queue_work(scifdev->intr_wq, &scifdev->intr_bh);
	return IRQ_HANDLED;
}
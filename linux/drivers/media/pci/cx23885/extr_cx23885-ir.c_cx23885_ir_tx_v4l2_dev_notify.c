#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct cx23885_dev {unsigned long ir_tx_notifications; int /*<<< orphan*/  ir_tx_work; struct v4l2_subdev* sd_cx25840; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX23885_IR_TX_FIFO_SERVICE_REQ ; 
 int V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ ; 
 int /*<<< orphan*/  cx23885_ir_tx_work_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct cx23885_dev* to_cx23885 (int /*<<< orphan*/ ) ; 

void cx23885_ir_tx_v4l2_dev_notify(struct v4l2_subdev *sd, u32 events)
{
	struct cx23885_dev *dev = to_cx23885(sd->v4l2_dev);
	unsigned long *notifications = &dev->ir_tx_notifications;

	if (events & V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ)
		set_bit(CX23885_IR_TX_FIFO_SERVICE_REQ, notifications);

	/*
	 * For the integrated AV core, we are already in a workqueue context.
	 * For the CX23888 integrated IR, we are in an interrupt context.
	 */
	if (sd == dev->sd_cx25840)
		cx23885_ir_tx_work_handler(&dev->ir_tx_work);
	else
		schedule_work(&dev->ir_tx_work);
}
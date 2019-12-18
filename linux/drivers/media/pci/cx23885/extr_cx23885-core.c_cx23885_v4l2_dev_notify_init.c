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
struct TYPE_2__ {int /*<<< orphan*/  notify; } ;
struct cx23885_dev {TYPE_1__ v4l2_dev; int /*<<< orphan*/  ir_tx_work; int /*<<< orphan*/  ir_rx_work; int /*<<< orphan*/  cx25840_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_av_work_handler ; 
 int /*<<< orphan*/  cx23885_ir_rx_work_handler ; 
 int /*<<< orphan*/  cx23885_ir_tx_work_handler ; 
 int /*<<< orphan*/  cx23885_v4l2_dev_notify ; 

__attribute__((used)) static void cx23885_v4l2_dev_notify_init(struct cx23885_dev *dev)
{
	INIT_WORK(&dev->cx25840_work, cx23885_av_work_handler);
	INIT_WORK(&dev->ir_rx_work, cx23885_ir_rx_work_handler);
	INIT_WORK(&dev->ir_tx_work, cx23885_ir_tx_work_handler);
	dev->v4l2_dev.notify = cx23885_v4l2_dev_notify;
}
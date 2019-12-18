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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct cx23885_dev {struct v4l2_subdev* sd_ir; } ;

/* Variables and functions */
#define  V4L2_SUBDEV_IR_RX_NOTIFY 129 
#define  V4L2_SUBDEV_IR_TX_NOTIFY 128 
 int /*<<< orphan*/  cx23885_ir_rx_v4l2_dev_notify (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_ir_tx_v4l2_dev_notify (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct cx23885_dev* to_cx23885 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx23885_v4l2_dev_notify(struct v4l2_subdev *sd,
				    unsigned int notification, void *arg)
{
	struct cx23885_dev *dev;

	if (sd == NULL)
		return;

	dev = to_cx23885(sd->v4l2_dev);

	switch (notification) {
	case V4L2_SUBDEV_IR_RX_NOTIFY: /* Possibly called in an IRQ context */
		if (sd == dev->sd_ir)
			cx23885_ir_rx_v4l2_dev_notify(sd, *(u32 *)arg);
		break;
	case V4L2_SUBDEV_IR_TX_NOTIFY: /* Possibly called in an IRQ context */
		if (sd == dev->sd_ir)
			cx23885_ir_tx_v4l2_dev_notify(sd, *(u32 *)arg);
		break;
	}
}
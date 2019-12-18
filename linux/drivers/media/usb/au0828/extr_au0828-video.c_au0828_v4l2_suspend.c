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
struct urb {int dummy; } ;
struct TYPE_2__ {int num_bufs; struct urb** urb; } ;
struct au0828_dev {scalar_t__ stream_state; int /*<<< orphan*/  vbi_timeout; scalar_t__ vbi_timeout_running; int /*<<< orphan*/  vid_timeout; scalar_t__ vid_timeout_running; TYPE_1__ isoc_ctl; } ;

/* Variables and functions */
 scalar_t__ STREAM_ON ; 
 int /*<<< orphan*/  au0828_analog_stream_disable (struct au0828_dev*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

void au0828_v4l2_suspend(struct au0828_dev *dev)
{
	struct urb *urb;
	int i;

	pr_info("stopping V4L2\n");

	if (dev->stream_state == STREAM_ON) {
		pr_info("stopping V4L2 active URBs\n");
		au0828_analog_stream_disable(dev);
		/* stop urbs */
		for (i = 0; i < dev->isoc_ctl.num_bufs; i++) {
			urb = dev->isoc_ctl.urb[i];
			if (urb) {
				if (!irqs_disabled())
					usb_kill_urb(urb);
				else
					usb_unlink_urb(urb);
			}
		}
	}

	if (dev->vid_timeout_running)
		del_timer_sync(&dev->vid_timeout);
	if (dev->vbi_timeout_running)
		del_timer_sync(&dev->vbi_timeout);
}
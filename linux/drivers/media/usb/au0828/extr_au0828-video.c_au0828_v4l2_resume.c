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
struct TYPE_2__ {int num_bufs; int /*<<< orphan*/ * urb; } ;
struct au0828_dev {scalar_t__ stream_state; TYPE_1__ isoc_ctl; int /*<<< orphan*/  vbi_timeout; scalar_t__ vbi_timeout_running; int /*<<< orphan*/  vid_timeout; scalar_t__ vid_timeout_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 scalar_t__ STREAM_ON ; 
 int /*<<< orphan*/  au0828_analog_stream_enable (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_analog_stream_reset (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_i2s_init (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_init_tuner (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_isocdbg (char*,int,int) ; 
 int /*<<< orphan*/  au0828_stream_interrupt (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_uninit_isoc (struct au0828_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void au0828_v4l2_resume(struct au0828_dev *dev)
{
	int i, rc;

	pr_info("restarting V4L2\n");

	if (dev->stream_state == STREAM_ON) {
		au0828_stream_interrupt(dev);
		au0828_init_tuner(dev);
	}

	if (dev->vid_timeout_running)
		mod_timer(&dev->vid_timeout, jiffies + (HZ / 10));
	if (dev->vbi_timeout_running)
		mod_timer(&dev->vbi_timeout, jiffies + (HZ / 10));

	/* If we were doing ac97 instead of i2s, it would go here...*/
	au0828_i2s_init(dev);

	au0828_analog_stream_enable(dev);

	if (!(dev->stream_state == STREAM_ON)) {
		au0828_analog_stream_reset(dev);
		/* submit urbs */
		for (i = 0; i < dev->isoc_ctl.num_bufs; i++) {
			rc = usb_submit_urb(dev->isoc_ctl.urb[i], GFP_ATOMIC);
			if (rc) {
				au0828_isocdbg("submit of urb %i failed (error=%i)\n",
					       i, rc);
				au0828_uninit_isoc(dev);
			}
		}
	}
}
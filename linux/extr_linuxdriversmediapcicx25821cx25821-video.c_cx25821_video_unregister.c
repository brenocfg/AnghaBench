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
struct cx25821_dev {TYPE_1__* channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdl; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void cx25821_video_unregister(struct cx25821_dev *dev, int chan_num)
{
	cx_clear(PCI_INT_MSK, 1);

	if (video_is_registered(&dev->channels[chan_num].vdev)) {
		video_unregister_device(&dev->channels[chan_num].vdev);
		v4l2_ctrl_handler_free(&dev->channels[chan_num].hdl);
	}
}
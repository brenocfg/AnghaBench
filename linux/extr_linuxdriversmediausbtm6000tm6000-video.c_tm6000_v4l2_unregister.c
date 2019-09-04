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
struct tm6000_core {int /*<<< orphan*/  radio_dev; int /*<<< orphan*/  vfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  tm6000_free_urb_buffers (struct tm6000_core*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

int tm6000_v4l2_unregister(struct tm6000_core *dev)
{
	video_unregister_device(&dev->vfd);

	/* if URB buffers are still allocated free them now */
	tm6000_free_urb_buffers(dev);

	video_unregister_device(&dev->radio_dev);
	return 0;
}
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
struct video_device {int dummy; } ;
struct stk_camera {int /*<<< orphan*/  interface; int /*<<< orphan*/ * isobufs; int /*<<< orphan*/ * sio_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 
 struct stk_camera* vdev_to_camera (struct video_device*) ; 

__attribute__((used)) static void stk_v4l_dev_release(struct video_device *vd)
{
	struct stk_camera *dev = vdev_to_camera(vd);

	if (dev->sio_bufs != NULL || dev->isobufs != NULL)
		pr_err("We are leaking memory\n");
	usb_put_intf(dev->interface);
}
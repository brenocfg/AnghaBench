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
struct video_device {int /*<<< orphan*/ * ioctl_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ivtv_ioctl_ops ; 

void ivtv_set_funcs(struct video_device *vdev)
{
	vdev->ioctl_ops = &ivtv_ioctl_ops;
}
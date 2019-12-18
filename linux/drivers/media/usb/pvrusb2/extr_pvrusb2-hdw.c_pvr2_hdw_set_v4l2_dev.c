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
struct video_device {int /*<<< orphan*/ * v4l2_dev; } ;
struct pvr2_hdw {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */

void pvr2_hdw_set_v4l2_dev(struct pvr2_hdw *hdw, struct video_device *vdev)
{
	vdev->v4l2_dev = &hdw->v4l2_dev;
}
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

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct video_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void v4l2_device_release_subdev_node(struct video_device *vdev)
{
	v4l2_subdev_release(video_get_drvdata(vdev));
	kfree(vdev);
}
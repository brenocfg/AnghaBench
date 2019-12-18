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
struct video_device {int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  entity; } ;
struct camif_dev {TYPE_1__* vp; } ;
struct TYPE_2__ {struct video_device vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

void s3c_camif_unregister_video_node(struct camif_dev *camif, int idx)
{
	struct video_device *vfd = &camif->vp[idx].vdev;

	if (video_is_registered(vfd)) {
		video_unregister_device(vfd);
		media_entity_cleanup(&vfd->entity);
		v4l2_ctrl_handler_free(vfd->ctrl_handler);
	}
}
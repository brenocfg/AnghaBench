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
struct vfe_device {TYPE_1__* line; int /*<<< orphan*/  stream_lock; int /*<<< orphan*/  power_lock; } ;
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct camss_video {int dummy; } ;
struct TYPE_2__ {struct camss_video video_out; struct v4l2_subdev subdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_video_unregister (struct camss_video*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

void msm_vfe_unregister_entities(struct vfe_device *vfe)
{
	int i;

	mutex_destroy(&vfe->power_lock);
	mutex_destroy(&vfe->stream_lock);

	for (i = 0; i < ARRAY_SIZE(vfe->line); i++) {
		struct v4l2_subdev *sd = &vfe->line[i].subdev;
		struct camss_video *video_out = &vfe->line[i].video_out;

		msm_video_unregister(video_out);
		v4l2_device_unregister_subdev(sd);
		media_entity_cleanup(&sd->entity);
	}
}
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
struct video_mux {int /*<<< orphan*/  lock; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {unsigned int num_pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,unsigned int) ; 
 struct video_mux* v4l2_subdev_to_video_mux (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt video_mux_format_mbus_default ; 

__attribute__((used)) static int video_mux_init_cfg(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg)
{
	struct video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	struct v4l2_mbus_framefmt *mbusformat;
	unsigned int i;

	mutex_lock(&vmux->lock);

	for (i = 0; i < sd->entity.num_pads; i++) {
		mbusformat = v4l2_subdev_get_try_format(sd, cfg, i);
		*mbusformat = video_mux_format_mbus_default;
	}

	mutex_unlock(&vmux->lock);

	return 0;
}
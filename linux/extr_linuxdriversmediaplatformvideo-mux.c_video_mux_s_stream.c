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
struct video_mux {int active; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pads; } ;
struct v4l2_subdev {int /*<<< orphan*/  dev; TYPE_1__ entity; } ;
struct media_pad {int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOLINK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_mux* v4l2_subdev_to_video_mux (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int video_mux_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	struct v4l2_subdev *upstream_sd;
	struct media_pad *pad;

	if (vmux->active == -1) {
		dev_err(sd->dev, "Can not start streaming on inactive mux\n");
		return -EINVAL;
	}

	pad = media_entity_remote_pad(&sd->entity.pads[vmux->active]);
	if (!pad) {
		dev_err(sd->dev, "Failed to find remote source pad\n");
		return -ENOLINK;
	}

	if (!is_media_entity_v4l2_subdev(pad->entity)) {
		dev_err(sd->dev, "Upstream entity is not a v4l2 subdev\n");
		return -ENODEV;
	}

	upstream_sd = media_entity_to_v4l2_subdev(pad->entity);

	return v4l2_subdev_call(upstream_sd, video, s_stream, enable);
}
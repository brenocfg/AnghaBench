#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; scalar_t__ code; } ;
struct v4l2_subdev_format {TYPE_2__ format; void* which; int /*<<< orphan*/  pad; } ;
struct TYPE_3__ {struct media_pad* pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
struct media_pad {int flags; int /*<<< orphan*/  index; int /*<<< orphan*/  entity; } ;
struct fimc_isp {struct v4l2_subdev subdev; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int EPIPE ; 
 int MEDIA_PAD_FL_SINK ; 
 void* V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,struct media_pad*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int isp_video_pipeline_validate(struct fimc_isp *isp)
{
	struct v4l2_subdev *sd = &isp->subdev;
	struct v4l2_subdev_format sink_fmt, src_fmt;
	struct media_pad *pad;
	int ret;

	while (1) {
		/* Retrieve format at the sink pad */
		pad = &sd->entity.pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;
		sink_fmt.pad = pad->index;
		sink_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, NULL, &sink_fmt);
		if (ret < 0 && ret != -ENOIOCTLCMD)
			return -EPIPE;

		/* Retrieve format at the source pad */
		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		sd = media_entity_to_v4l2_subdev(pad->entity);
		src_fmt.pad = pad->index;
		src_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, NULL, &src_fmt);
		if (ret < 0 && ret != -ENOIOCTLCMD)
			return -EPIPE;

		if (src_fmt.format.width != sink_fmt.format.width ||
		    src_fmt.format.height != sink_fmt.format.height ||
		    src_fmt.format.code != sink_fmt.format.code)
			return -EPIPE;
	}

	return 0;
}
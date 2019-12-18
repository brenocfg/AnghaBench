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
struct v4l2_subdev {int dummy; } ;
struct media_pad {int /*<<< orphan*/  entity; } ;
struct media_entity {unsigned int num_pads; TYPE_1__* pads; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct media_pad* media_entity_remote_pad (TYPE_1__*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

int vimc_pipeline_s_stream(struct media_entity *ent, int enable)
{
	struct v4l2_subdev *sd;
	struct media_pad *pad;
	unsigned int i;
	int ret;

	for (i = 0; i < ent->num_pads; i++) {
		if (ent->pads[i].flags & MEDIA_PAD_FL_SOURCE)
			continue;

		/* Start the stream in the subdevice direct connected */
		pad = media_entity_remote_pad(&ent->pads[i]);
		if (!pad)
			continue;

		if (!is_media_entity_v4l2_subdev(pad->entity))
			return -EINVAL;

		sd = media_entity_to_v4l2_subdev(pad->entity);
		ret = v4l2_subdev_call(sd, video, s_stream, enable);
		if (ret && ret != -ENOIOCTLCMD)
			return ret;
	}

	return 0;
}
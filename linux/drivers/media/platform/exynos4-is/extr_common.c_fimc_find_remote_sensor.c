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
struct TYPE_2__ {struct media_pad* pads; } ;
struct v4l2_subdev {scalar_t__ grp_id; TYPE_1__ entity; } ;
struct media_pad {int flags; int /*<<< orphan*/  entity; } ;
struct media_entity {struct media_pad* pads; } ;

/* Variables and functions */
 scalar_t__ GRP_ID_FIMC_IS_SENSOR ; 
 scalar_t__ GRP_ID_SENSOR ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 

struct v4l2_subdev *fimc_find_remote_sensor(struct media_entity *entity)
{
	struct media_pad *pad = &entity->pads[0];
	struct v4l2_subdev *sd;

	while (pad->flags & MEDIA_PAD_FL_SINK) {
		/* source pad */
		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		sd = media_entity_to_v4l2_subdev(pad->entity);

		if (sd->grp_id == GRP_ID_FIMC_IS_SENSOR ||
		    sd->grp_id == GRP_ID_SENSOR)
			return sd;
		/* sink pad */
		pad = &sd->entity.pads[0];
	}
	return NULL;
}
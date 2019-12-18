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
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {scalar_t__ function; struct media_pad* pads; } ;

/* Variables and functions */
 scalar_t__ MEDIA_ENT_F_CAM_SENSOR ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 

struct media_entity *camss_find_sensor(struct media_entity *entity)
{
	struct media_pad *pad;

	while (1) {
		pad = &entity->pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			return NULL;

		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			return NULL;

		entity = pad->entity;

		if (entity->function == MEDIA_ENT_F_CAM_SENSOR)
			return entity;
	}
}
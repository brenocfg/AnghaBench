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
struct stm32_dcmi {TYPE_1__* vdev; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {struct media_pad* pads; } ;
struct TYPE_2__ {struct media_entity entity; } ;

/* Variables and functions */
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 

__attribute__((used)) static struct media_entity *dcmi_find_source(struct stm32_dcmi *dcmi)
{
	struct media_entity *entity = &dcmi->vdev->entity;
	struct media_pad *pad;

	/* Walk searching for entity having no sink */
	while (1) {
		pad = &entity->pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;

		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		entity = pad->entity;
	}

	return entity;
}
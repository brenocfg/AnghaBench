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
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct uvc_entity {TYPE_2__* vdev; TYPE_1__ subdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 scalar_t__ UVC_ENTITY_TYPE (struct uvc_entity*) ; 
 scalar_t__ UVC_TT_STREAMING ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 

void uvc_mc_cleanup_entity(struct uvc_entity *entity)
{
	if (UVC_ENTITY_TYPE(entity) != UVC_TT_STREAMING)
		media_entity_cleanup(&entity->subdev.entity);
	else if (entity->vdev != NULL)
		media_entity_cleanup(&entity->vdev->entity);
}
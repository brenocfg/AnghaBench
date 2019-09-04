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
struct TYPE_4__ {int /*<<< orphan*/  entity; scalar_t__ ctrl_handler; } ;
struct vsp1_entity {TYPE_2__ subdev; int /*<<< orphan*/  config; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (struct vsp1_entity*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vsp1_entity*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (scalar_t__) ; 
 int /*<<< orphan*/  v4l2_subdev_free_pad_config (int /*<<< orphan*/ ) ; 

void vsp1_entity_destroy(struct vsp1_entity *entity)
{
	if (entity->ops && entity->ops->destroy)
		entity->ops->destroy(entity);
	if (entity->subdev.ctrl_handler)
		v4l2_ctrl_handler_free(entity->subdev.ctrl_handler);
	v4l2_subdev_free_pad_config(entity->config);
	media_entity_cleanup(&entity->subdev.entity);
}
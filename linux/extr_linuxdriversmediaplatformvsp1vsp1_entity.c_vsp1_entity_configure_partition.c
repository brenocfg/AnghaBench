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
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {TYPE_1__* ops; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* configure_partition ) (struct vsp1_entity*,struct vsp1_pipeline*,struct vsp1_dl_list*,struct vsp1_dl_body*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vsp1_entity*,struct vsp1_pipeline*,struct vsp1_dl_list*,struct vsp1_dl_body*) ; 

void vsp1_entity_configure_partition(struct vsp1_entity *entity,
				     struct vsp1_pipeline *pipe,
				     struct vsp1_dl_list *dl,
				     struct vsp1_dl_body *dlb)
{
	if (entity->ops->configure_partition)
		entity->ops->configure_partition(entity, pipe, dl, dlb);
}
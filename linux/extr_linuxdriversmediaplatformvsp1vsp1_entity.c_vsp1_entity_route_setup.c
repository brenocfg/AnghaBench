#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vsp1_pipeline {TYPE_2__* output; } ;
struct vsp1_entity {scalar_t__ type; size_t sink_pad; TYPE_5__* route; TYPE_4__* sink; struct vsp1_entity** sources; } ;
struct vsp1_dl_body {int dummy; } ;
struct TYPE_10__ {int output; scalar_t__ reg; } ;
struct TYPE_9__ {TYPE_3__* route; } ;
struct TYPE_8__ {int* inputs; } ;
struct TYPE_6__ {int index; } ;
struct TYPE_7__ {TYPE_1__ entity; } ;

/* Variables and functions */
 scalar_t__ VI6_DPR_HGO_SMPPT ; 
 scalar_t__ VI6_DPR_HGT_SMPPT ; 
 int VI6_DPR_ROUTE_BRSSEL ; 
 int VI6_DPR_SMPPT_PT_SHIFT ; 
 int VI6_DPR_SMPPT_TGW_SHIFT ; 
 scalar_t__ VSP1_ENTITY_BRS ; 
 scalar_t__ VSP1_ENTITY_HGO ; 
 scalar_t__ VSP1_ENTITY_HGT ; 
 int /*<<< orphan*/  vsp1_dl_body_write (struct vsp1_dl_body*,scalar_t__,int) ; 

void vsp1_entity_route_setup(struct vsp1_entity *entity,
			     struct vsp1_pipeline *pipe,
			     struct vsp1_dl_body *dlb)
{
	struct vsp1_entity *source;
	u32 route;

	if (entity->type == VSP1_ENTITY_HGO) {
		u32 smppt;

		/*
		 * The HGO is a special case, its routing is configured on the
		 * sink pad.
		 */
		source = entity->sources[0];
		smppt = (pipe->output->entity.index << VI6_DPR_SMPPT_TGW_SHIFT)
		      | (source->route->output << VI6_DPR_SMPPT_PT_SHIFT);

		vsp1_dl_body_write(dlb, VI6_DPR_HGO_SMPPT, smppt);
		return;
	} else if (entity->type == VSP1_ENTITY_HGT) {
		u32 smppt;

		/*
		 * The HGT is a special case, its routing is configured on the
		 * sink pad.
		 */
		source = entity->sources[0];
		smppt = (pipe->output->entity.index << VI6_DPR_SMPPT_TGW_SHIFT)
		      | (source->route->output << VI6_DPR_SMPPT_PT_SHIFT);

		vsp1_dl_body_write(dlb, VI6_DPR_HGT_SMPPT, smppt);
		return;
	}

	source = entity;
	if (source->route->reg == 0)
		return;

	route = source->sink->route->inputs[source->sink_pad];
	/*
	 * The ILV and BRS share the same data path route. The extra BRSSEL bit
	 * selects between the ILV and BRS.
	 */
	if (source->type == VSP1_ENTITY_BRS)
		route |= VI6_DPR_ROUTE_BRSSEL;
	vsp1_dl_body_write(dlb, source->route->reg, route);
}
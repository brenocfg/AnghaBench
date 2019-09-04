#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int scaling_change; int bandwidth_change; int clock_change; int position_change; } ;
union surface_update_flags {TYPE_9__ bits; } ;
struct dc_surface_update {TYPE_8__* surface; TYPE_6__* scaling_info; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_16__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_13__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_11__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_17__ {TYPE_7__ dst_rect; TYPE_4__ clip_rect; TYPE_2__ src_rect; union surface_update_flags update_flags; } ;
struct TYPE_14__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_12__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_15__ {TYPE_5__ dst_rect; TYPE_3__ clip_rect; TYPE_1__ src_rect; } ;

/* Variables and functions */
 int UPDATE_TYPE_FAST ; 
 int UPDATE_TYPE_FULL ; 
 int UPDATE_TYPE_MED ; 

__attribute__((used)) static enum surface_update_type get_scaling_info_update_type(
		const struct dc_surface_update *u)
{
	union surface_update_flags *update_flags = &u->surface->update_flags;

	if (!u->scaling_info)
		return UPDATE_TYPE_FAST;

	if (u->scaling_info->clip_rect.width != u->surface->clip_rect.width
			|| u->scaling_info->clip_rect.height != u->surface->clip_rect.height
			|| u->scaling_info->dst_rect.width != u->surface->dst_rect.width
			|| u->scaling_info->dst_rect.height != u->surface->dst_rect.height) {
		update_flags->bits.scaling_change = 1;

		if ((u->scaling_info->dst_rect.width < u->surface->dst_rect.width
			|| u->scaling_info->dst_rect.height < u->surface->dst_rect.height)
				&& (u->scaling_info->dst_rect.width < u->surface->src_rect.width
					|| u->scaling_info->dst_rect.height < u->surface->src_rect.height))
			/* Making dst rect smaller requires a bandwidth change */
			update_flags->bits.bandwidth_change = 1;
	}

	if (u->scaling_info->src_rect.width != u->surface->src_rect.width
		|| u->scaling_info->src_rect.height != u->surface->src_rect.height) {

		update_flags->bits.scaling_change = 1;
		if (u->scaling_info->src_rect.width > u->surface->src_rect.width
				&& u->scaling_info->src_rect.height > u->surface->src_rect.height)
			/* Making src rect bigger requires a bandwidth change */
			update_flags->bits.clock_change = 1;
	}

	if (u->scaling_info->src_rect.x != u->surface->src_rect.x
			|| u->scaling_info->src_rect.y != u->surface->src_rect.y
			|| u->scaling_info->clip_rect.x != u->surface->clip_rect.x
			|| u->scaling_info->clip_rect.y != u->surface->clip_rect.y
			|| u->scaling_info->dst_rect.x != u->surface->dst_rect.x
			|| u->scaling_info->dst_rect.y != u->surface->dst_rect.y)
		update_flags->bits.position_change = 1;

	if (update_flags->bits.clock_change
			|| update_flags->bits.bandwidth_change)
		return UPDATE_TYPE_FULL;

	if (update_flags->bits.scaling_change
			|| update_flags->bits.position_change)
		return UPDATE_TYPE_MED;

	return UPDATE_TYPE_FAST;
}
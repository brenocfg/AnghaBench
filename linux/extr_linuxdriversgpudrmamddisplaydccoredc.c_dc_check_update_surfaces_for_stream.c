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
struct dc_surface_update {TYPE_2__* surface; } ;
struct dc_stream_update {int dummy; } ;
struct dc_stream_status {int dummy; } ;
struct dc {int dummy; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_3__ {int raw; } ;
struct TYPE_4__ {TYPE_1__ update_flags; } ;

/* Variables and functions */
 int UPDATE_TYPE_FULL ; 
 int check_update_surfaces_for_stream (struct dc*,struct dc_surface_update*,int,struct dc_stream_update*,struct dc_stream_status const*) ; 

enum surface_update_type dc_check_update_surfaces_for_stream(
		struct dc *dc,
		struct dc_surface_update *updates,
		int surface_count,
		struct dc_stream_update *stream_update,
		const struct dc_stream_status *stream_status)
{
	int i;
	enum surface_update_type type;

	for (i = 0; i < surface_count; i++)
		updates[i].surface->update_flags.raw = 0;

	type = check_update_surfaces_for_stream(dc, updates, surface_count, stream_update, stream_status);
	if (type == UPDATE_TYPE_FULL)
		for (i = 0; i < surface_count; i++)
			updates[i].surface->update_flags.raw = 0xFFFFFFFF;

	return type;
}
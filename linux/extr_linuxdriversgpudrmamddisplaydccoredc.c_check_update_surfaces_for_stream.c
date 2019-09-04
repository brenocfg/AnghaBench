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
struct dc_surface_update {int dummy; } ;
struct dc_stream_update {int dummy; } ;
struct dc_stream_status {int plane_count; } ;
struct dc {int dummy; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;

/* Variables and functions */
 int UPDATE_TYPE_FAST ; 
 int UPDATE_TYPE_FULL ; 
 int det_surface_update (struct dc*,struct dc_surface_update*) ; 
 int /*<<< orphan*/  elevate_update_type (int*,int) ; 

__attribute__((used)) static enum surface_update_type check_update_surfaces_for_stream(
		struct dc *dc,
		struct dc_surface_update *updates,
		int surface_count,
		struct dc_stream_update *stream_update,
		const struct dc_stream_status *stream_status)
{
	int i;
	enum surface_update_type overall_type = UPDATE_TYPE_FAST;

	if (stream_status == NULL || stream_status->plane_count != surface_count)
		return UPDATE_TYPE_FULL;

	if (stream_update)
		return UPDATE_TYPE_FULL;

	for (i = 0 ; i < surface_count; i++) {
		enum surface_update_type type =
				det_surface_update(dc, &updates[i]);

		if (type == UPDATE_TYPE_FULL)
			return type;

		elevate_update_type(&overall_type, type);
	}

	return overall_type;
}
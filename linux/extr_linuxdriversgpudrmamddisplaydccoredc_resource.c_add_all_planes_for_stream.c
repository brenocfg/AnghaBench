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
struct dc_validation_set {int plane_count; int /*<<< orphan*/ * plane_states; struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;
struct dc_state {int dummy; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_add_plane_to_context (struct dc const*,struct dc_stream_state*,int /*<<< orphan*/ ,struct dc_state*) ; 
 int /*<<< orphan*/  dm_error (char*,struct dc_stream_state*) ; 

__attribute__((used)) static bool add_all_planes_for_stream(
		const struct dc *dc,
		struct dc_stream_state *stream,
		const struct dc_validation_set set[],
		int set_count,
		struct dc_state *context)
{
	int i, j;

	for (i = 0; i < set_count; i++)
		if (set[i].stream == stream)
			break;

	if (i == set_count) {
		dm_error("Stream %p not found in set!\n", stream);
		return false;
	}

	for (j = 0; j < set[i].plane_count; j++)
		if (!dc_add_plane_to_context(dc, stream, set[i].plane_states[j], context))
			return false;

	return true;
}
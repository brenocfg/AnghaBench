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
struct dc_stream_state {int dummy; } ;
struct dc_state {int stream_count; struct dc_stream_state** streams; } ;

/* Variables and functions */
 scalar_t__ are_stream_backends_same (struct dc_stream_state*,struct dc_stream_state*) ; 

bool resource_is_stream_unchanged(
	struct dc_state *old_context, struct dc_stream_state *stream)
{
	int i;

	for (i = 0; i < old_context->stream_count; i++) {
		struct dc_stream_state *old_stream = old_context->streams[i];

		if (are_stream_backends_same(old_stream, stream))
				return true;
	}

	return false;
}
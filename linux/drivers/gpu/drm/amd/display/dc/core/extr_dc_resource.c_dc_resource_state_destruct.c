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
struct dc_state {int stream_count; int /*<<< orphan*/ ** streams; TYPE_1__* stream_status; } ;
struct TYPE_2__ {int plane_count; int /*<<< orphan*/ * plane_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_plane_state_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_stream_release (int /*<<< orphan*/ *) ; 

void dc_resource_state_destruct(struct dc_state *context)
{
	int i, j;

	for (i = 0; i < context->stream_count; i++) {
		for (j = 0; j < context->stream_status[i].plane_count; j++)
			dc_plane_state_release(
				context->stream_status[i].plane_states[j]);

		context->stream_status[i].plane_count = 0;
		dc_stream_release(context->streams[i]);
		context->streams[i] = NULL;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct dc_stream_state {int dummy; } ;
struct dc_static_screen_events {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_static_screen_control ) (struct pipe_ctx**,int,struct dc_static_screen_events const*) ;} ;
struct dc {TYPE_3__ hwss; TYPE_2__* current_state; } ;
struct TYPE_4__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_5__ {TYPE_1__ res_ctx; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx**,int,struct dc_static_screen_events const*) ; 

void dc_stream_set_static_screen_events(struct dc *dc,
		struct dc_stream_state **streams,
		int num_streams,
		const struct dc_static_screen_events *events)
{
	int i = 0;
	int j = 0;
	struct pipe_ctx *pipes_affected[MAX_PIPES];
	int num_pipes_affected = 0;

	for (i = 0; i < num_streams; i++) {
		struct dc_stream_state *stream = streams[i];

		for (j = 0; j < MAX_PIPES; j++) {
			if (dc->current_state->res_ctx.pipe_ctx[j].stream
					== stream) {
				pipes_affected[num_pipes_affected++] =
						&dc->current_state->res_ctx.pipe_ctx[j];
			}
		}
	}

	dc->hwss.set_static_screen_control(pipes_affected, num_pipes_affected, events);
}
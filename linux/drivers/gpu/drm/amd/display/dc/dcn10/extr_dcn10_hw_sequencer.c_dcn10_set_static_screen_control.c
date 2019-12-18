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
struct TYPE_5__ {TYPE_3__* tg; } ;
struct pipe_ctx {TYPE_2__ stream_res; } ;
struct dc_static_screen_events {scalar_t__ force_trigger; scalar_t__ cursor_update; scalar_t__ surface_update; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_static_screen_control ) (TYPE_3__*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static void dcn10_set_static_screen_control(struct pipe_ctx **pipe_ctx,
		int num_pipes, const struct dc_static_screen_events *events)
{
	unsigned int i;
	unsigned int value = 0;

	if (events->surface_update)
		value |= 0x80;
	if (events->cursor_update)
		value |= 0x2;
	if (events->force_trigger)
		value |= 0x1;

	for (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->
			set_static_screen_control(pipe_ctx[i]->stream_res.tg, value);
}
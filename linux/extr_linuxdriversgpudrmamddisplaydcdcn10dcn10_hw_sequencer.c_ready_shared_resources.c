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
struct dc_state {scalar_t__ stream_count; } ;
struct dc {TYPE_1__* current_state; } ;
struct TYPE_2__ {scalar_t__ stream_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_pplib_apply_display_requirements (struct dc*,struct dc_state*) ; 

__attribute__((used)) static void ready_shared_resources(struct dc *dc, struct dc_state *context)
{
	/* S0i2 message */
	if (dc->current_state->stream_count == 0 &&
			context->stream_count != 0)
		dcn10_pplib_apply_display_requirements(dc, context);
}
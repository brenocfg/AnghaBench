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
typedef  size_t uint8_t ;
struct dc_state {scalar_t__ stream_count; scalar_t__* streams; } ;
struct dc {TYPE_1__* current_state; } ;
struct TYPE_2__ {scalar_t__ stream_count; scalar_t__* streams; } ;

/* Variables and functions */

__attribute__((used)) static bool context_changed(
		struct dc *dc,
		struct dc_state *context)
{
	uint8_t i;

	if (context->stream_count != dc->current_state->stream_count)
		return true;

	for (i = 0; i < dc->current_state->stream_count; i++) {
		if (dc->current_state->streams[i] != context->streams[i])
			return true;
	}

	return false;
}
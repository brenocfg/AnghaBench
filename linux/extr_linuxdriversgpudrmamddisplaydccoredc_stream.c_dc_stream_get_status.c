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
typedef  size_t uint8_t ;
struct dc_stream_status {int dummy; } ;
struct dc_stream_state {TYPE_1__* ctx; } ;
struct dc {TYPE_2__* current_state; } ;
struct TYPE_4__ {size_t stream_count; struct dc_stream_status* stream_status; struct dc_stream_state** streams; } ;
struct TYPE_3__ {struct dc* dc; } ;

/* Variables and functions */

struct dc_stream_status *dc_stream_get_status(
	struct dc_stream_state *stream)
{
	uint8_t i;
	struct dc  *dc = stream->ctx->dc;

	for (i = 0; i < dc->current_state->stream_count; i++) {
		if (stream == dc->current_state->streams[i])
			return &dc->current_state->stream_status[i];
	}

	return NULL;
}
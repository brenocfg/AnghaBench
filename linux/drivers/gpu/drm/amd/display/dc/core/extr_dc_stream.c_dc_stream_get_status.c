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
struct dc_stream_status {int dummy; } ;
struct dc_stream_state {TYPE_1__* ctx; } ;
struct dc {int /*<<< orphan*/  current_state; } ;
struct TYPE_2__ {struct dc* dc; } ;

/* Variables and functions */
 struct dc_stream_status* dc_stream_get_status_from_state (int /*<<< orphan*/ ,struct dc_stream_state*) ; 

struct dc_stream_status *dc_stream_get_status(
	struct dc_stream_state *stream)
{
	struct dc *dc = stream->ctx->dc;
	return dc_stream_get_status_from_state(dc->current_state, stream);
}
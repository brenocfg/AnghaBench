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
struct dc_stream_state {int dummy; } ;
struct dc {TYPE_1__* current_state; } ;
struct TYPE_2__ {size_t stream_count; struct dc_stream_state** streams; } ;

/* Variables and functions */

struct dc_stream_state *dc_get_stream_at_index(struct dc *dc, uint8_t i)
{
	if (i < dc->current_state->stream_count)
		return dc->current_state->streams[i];
	return NULL;
}
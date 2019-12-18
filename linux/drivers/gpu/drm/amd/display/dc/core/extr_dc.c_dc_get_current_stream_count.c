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
typedef  int /*<<< orphan*/  uint8_t ;
struct dc {TYPE_1__* current_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  stream_count; } ;

/* Variables and functions */

uint8_t dc_get_current_stream_count(struct dc *dc)
{
	return dc->current_state->stream_count;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct int_ch_state {scalar_t__ service_counter; scalar_t__ request_counter; scalar_t__ level; } ;
struct dim_channel {int /*<<< orphan*/  done_sw_buffers_number; struct int_ch_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_ERR_UNDERFLOW ; 
 int /*<<< orphan*/  DIM_NO_ERROR ; 

__attribute__((used)) static u8 channel_service(struct dim_channel *ch)
{
	struct int_ch_state *const state = &ch->state;

	if (state->service_counter != state->request_counter) {
		state->service_counter++;
		if (state->level == 0)
			return DIM_ERR_UNDERFLOW;

		--state->level;
		ch->done_sw_buffers_number++;
	}

	return DIM_NO_ERROR;
}
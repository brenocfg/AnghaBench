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
struct int_ch_state {int idx2; int /*<<< orphan*/  request_counter; } ;
struct dim_channel {int /*<<< orphan*/  addr; struct int_ch_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  service_channel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool channel_service_interrupt(struct dim_channel *ch)
{
	struct int_ch_state *const state = &ch->state;

	if (!service_channel(ch->addr, state->idx2))
		return false;

	state->idx2 ^= 1;
	state->request_counter++;
	return true;
}
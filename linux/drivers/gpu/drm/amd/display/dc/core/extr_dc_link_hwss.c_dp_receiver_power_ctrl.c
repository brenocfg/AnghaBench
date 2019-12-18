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
typedef  int /*<<< orphan*/  uint8_t ;
struct dc_link {scalar_t__ sync_lt_in_progress; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 int /*<<< orphan*/  DP_POWER_STATE_D0 ; 
 int /*<<< orphan*/  DP_POWER_STATE_D3 ; 
 int /*<<< orphan*/  DP_SET_POWER ; 
 int /*<<< orphan*/  core_link_write_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void dp_receiver_power_ctrl(struct dc_link *link, bool on)
{
	uint8_t state;

	state = on ? DP_POWER_STATE_D0 : DP_POWER_STATE_D3;

	if (link->sync_lt_in_progress)
		return;

	core_link_write_dpcd(link, DP_SET_POWER, &state,
			sizeof(state));
}
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

/* Variables and functions */
 int /*<<< orphan*/  MODE0_GATE ; 
 int /*<<< orphan*/  MODE1_GATE ; 
 scalar_t__ POWER_MODE_CTRL_MODE_MODE1 ; 
 scalar_t__ get_power_mode () ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 

void sm750_set_current_gate(unsigned int gate)
{
	if (get_power_mode() == POWER_MODE_CTRL_MODE_MODE1)
		poke32(MODE1_GATE, gate);
	else
		poke32(MODE0_GATE, gate);
}
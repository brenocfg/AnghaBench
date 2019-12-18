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
 scalar_t__ backside_fan ; 
 int /*<<< orphan*/  cpu_max_all_fans () ; 
 scalar_t__ slots_fan ; 
 int /*<<< orphan*/  wf_control_set_max (scalar_t__) ; 

__attribute__((used)) static void set_fail_state(void)
{
	cpu_max_all_fans();

	if (backside_fan)
		wf_control_set_max(backside_fan);
	if (slots_fan)
		wf_control_set_max(slots_fan);
}
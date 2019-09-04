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
typedef  enum cpu_state_vals { ____Placeholder_cpu_state_vals } cpu_state_vals ;

/* Variables and functions */
 int CPU_STATE_ONLINE ; 

__attribute__((used)) static inline enum cpu_state_vals get_cpu_current_state(int cpu)
{
	return CPU_STATE_ONLINE;
}
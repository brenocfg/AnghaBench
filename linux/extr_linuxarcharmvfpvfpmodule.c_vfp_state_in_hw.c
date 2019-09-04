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
struct thread_info {int /*<<< orphan*/  vfpstate; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** vfp_current_hw_state ; 

__attribute__((used)) static bool vfp_state_in_hw(unsigned int cpu, struct thread_info *thread)
{
#ifdef CONFIG_SMP
	if (thread->vfpstate.hard.cpu != cpu)
		return false;
#endif
	return vfp_current_hw_state[cpu] == &thread->vfpstate;
}
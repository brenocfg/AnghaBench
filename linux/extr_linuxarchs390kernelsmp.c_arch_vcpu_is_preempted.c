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
 int /*<<< orphan*/  CIF_ENABLED_WAIT ; 
 scalar_t__ pcpu_devices ; 
 scalar_t__ pcpu_running (scalar_t__) ; 
 scalar_t__ test_cpu_flag_of (int /*<<< orphan*/ ,int) ; 

bool arch_vcpu_is_preempted(int cpu)
{
	if (test_cpu_flag_of(CIF_ENABLED_WAIT, cpu))
		return false;
	if (pcpu_running(pcpu_devices + cpu))
		return false;
	return true;
}
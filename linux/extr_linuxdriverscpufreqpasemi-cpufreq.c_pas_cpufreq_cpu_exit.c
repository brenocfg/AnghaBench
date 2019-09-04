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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_RUNNING ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 scalar_t__ sdcasr_mapbase ; 
 scalar_t__ sdcpwr_mapbase ; 
 scalar_t__ system_state ; 

__attribute__((used)) static int pas_cpufreq_cpu_exit(struct cpufreq_policy *policy)
{
	/*
	 * We don't support CPU hotplug. Don't unmap after the system
	 * has already made it to a running state.
	 */
	if (system_state >= SYSTEM_RUNNING)
		return 0;

	if (sdcasr_mapbase)
		iounmap(sdcasr_mapbase);
	if (sdcpwr_mapbase)
		iounmap(sdcpwr_mapbase);

	return 0;
}
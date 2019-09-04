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
typedef  int ssize_t ;

/* Variables and functions */
 char** energy_perf_strings ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t show_energy_performance_available_preferences(
				struct cpufreq_policy *policy, char *buf)
{
	int i = 0;
	int ret = 0;

	while (energy_perf_strings[i] != NULL)
		ret += sprintf(&buf[ret], "%s ", energy_perf_strings[i++]);

	ret += sprintf(&buf[ret], "\n");

	return ret;
}
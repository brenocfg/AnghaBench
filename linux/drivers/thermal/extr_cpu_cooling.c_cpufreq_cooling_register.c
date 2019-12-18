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
struct thermal_cooling_device {int dummy; } ;
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 struct thermal_cooling_device* __cpufreq_cooling_register (int /*<<< orphan*/ *,struct cpufreq_policy*,int /*<<< orphan*/ ) ; 

struct thermal_cooling_device *
cpufreq_cooling_register(struct cpufreq_policy *policy)
{
	return __cpufreq_cooling_register(NULL, policy, 0);
}
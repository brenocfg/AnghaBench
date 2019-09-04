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
struct powernowk8_target_arg {unsigned int newstate; struct cpufreq_policy* pol; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  powernowk8_target_fn ; 
 int work_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct powernowk8_target_arg*) ; 

__attribute__((used)) static int powernowk8_target(struct cpufreq_policy *pol, unsigned index)
{
	struct powernowk8_target_arg pta = { .pol = pol, .newstate = index };

	return work_on_cpu(pol->cpu, powernowk8_target_fn, &pta);
}
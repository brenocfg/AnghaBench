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
struct global_pstate_info {scalar_t__ last_gpstate_idx; scalar_t__ last_lpstate_idx; scalar_t__ last_sampled_time; scalar_t__ elapsed_time; scalar_t__ highest_lpstate_idx; } ;
struct cpufreq_policy {struct global_pstate_info* driver_data; } ;

/* Variables and functions */

__attribute__((used)) static inline void reset_gpstates(struct cpufreq_policy *policy)
{
	struct global_pstate_info *gpstates = policy->driver_data;

	gpstates->highest_lpstate_idx = 0;
	gpstates->elapsed_time = 0;
	gpstates->last_sampled_time = 0;
	gpstates->last_lpstate_idx = 0;
	gpstates->last_gpstate_idx = 0;
}
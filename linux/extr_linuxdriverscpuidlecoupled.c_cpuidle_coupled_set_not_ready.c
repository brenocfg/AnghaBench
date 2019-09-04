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
struct cpuidle_coupled {int online_count; int /*<<< orphan*/  ready_waiting_counts; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_WAITING_CPUS ; 
 int WAITING_BITS ; 
 int atomic_add_unless (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
inline int cpuidle_coupled_set_not_ready(struct cpuidle_coupled *coupled)
{
	int all;
	int ret;

	all = coupled->online_count | (coupled->online_count << WAITING_BITS);
	ret = atomic_add_unless(&coupled->ready_waiting_counts,
		-MAX_WAITING_CPUS, all);

	return ret ? 0 : -EINVAL;
}
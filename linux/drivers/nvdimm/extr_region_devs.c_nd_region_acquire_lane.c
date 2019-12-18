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
struct nd_region {unsigned int num_lanes; int /*<<< orphan*/  lane; } ;
struct nd_percpu_lane {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 unsigned int get_cpu () ; 
 unsigned int nr_cpu_ids ; 
 struct nd_percpu_lane* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

unsigned int nd_region_acquire_lane(struct nd_region *nd_region)
{
	unsigned int cpu, lane;

	cpu = get_cpu();
	if (nd_region->num_lanes < nr_cpu_ids) {
		struct nd_percpu_lane *ndl_lock, *ndl_count;

		lane = cpu % nd_region->num_lanes;
		ndl_count = per_cpu_ptr(nd_region->lane, cpu);
		ndl_lock = per_cpu_ptr(nd_region->lane, lane);
		if (ndl_count->count++ == 0)
			spin_lock(&ndl_lock->lock);
	} else
		lane = cpu;

	return lane;
}
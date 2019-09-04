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
 int NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS ; 
 int NUM_PPORT_PRIO ; 

__attribute__((used)) static int mlx5e_grp_per_prio_traffic_get_num_stats(void)
{
	return NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS * NUM_PPORT_PRIO;
}
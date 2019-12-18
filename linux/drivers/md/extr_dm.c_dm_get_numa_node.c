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
 int /*<<< orphan*/  DM_NUMA_NODE ; 
 int __dm_get_module_param_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dm_numa_node ; 
 scalar_t__ num_online_nodes () ; 

__attribute__((used)) static unsigned dm_get_numa_node(void)
{
	return __dm_get_module_param_int(&dm_numa_node,
					 DM_NUMA_NODE, num_online_nodes() - 1);
}
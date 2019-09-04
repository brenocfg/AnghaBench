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
typedef  int u32 ;
struct cpuinfo_x86 {int x86_max_cores; } ;

/* Variables and functions */
 int amd_get_nodes_per_socket () ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int smp_num_siblings ; 

__attribute__((used)) static u32 get_nbc_for_node(int node_id)
{
	struct cpuinfo_x86 *c = &boot_cpu_data;
	u32 cores_per_node;

	cores_per_node = (c->x86_max_cores * smp_num_siblings) / amd_get_nodes_per_socket();

	return cores_per_node * node_id;
}
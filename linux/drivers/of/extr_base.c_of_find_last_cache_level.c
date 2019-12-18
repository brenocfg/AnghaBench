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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_cpu_device_node_get (unsigned int) ; 
 struct device_node* of_find_next_cache_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

int of_find_last_cache_level(unsigned int cpu)
{
	u32 cache_level = 0;
	struct device_node *prev = NULL, *np = of_cpu_device_node_get(cpu);

	while (np) {
		prev = np;
		of_node_put(np);
		np = of_find_next_cache_node(np);
	}

	of_property_read_u32(prev, "cache-level", &cache_level);

	return cache_level;
}
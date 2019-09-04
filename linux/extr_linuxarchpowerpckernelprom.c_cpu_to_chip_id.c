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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_get_cpu_node (int,int /*<<< orphan*/ *) ; 
 int of_get_ibm_chip_id (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int cpu_to_chip_id(int cpu)
{
	struct device_node *np;

	np = of_get_cpu_node(cpu, NULL);
	if (!np)
		return -1;

	of_node_put(np);
	return of_get_ibm_chip_id(np);
}
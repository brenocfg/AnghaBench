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
 struct device_node* of_cpu_device_node_get (int) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static struct device_node *get_cpu_node_with_valid_op(int cpu)
{
	struct device_node *np = of_cpu_device_node_get(cpu);

	if (!of_get_property(np, "operating-points", NULL)) {
		of_node_put(np);
		np = NULL;
	}

	return np;
}
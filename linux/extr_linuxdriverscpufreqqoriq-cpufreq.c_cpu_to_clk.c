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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_present (int) ; 
 struct clk* of_clk_get (struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_cpu_node (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static struct clk *cpu_to_clk(int cpu)
{
	struct device_node *np;
	struct clk *clk;

	if (!cpu_present(cpu))
		return NULL;

	np = of_get_cpu_node(cpu, NULL);
	if (!np)
		return NULL;

	clk = of_clk_get(np, 0);
	of_node_put(np);
	return clk;
}
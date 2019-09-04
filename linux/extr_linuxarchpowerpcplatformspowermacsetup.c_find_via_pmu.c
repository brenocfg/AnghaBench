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
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  printk (char*) ; 

int find_via_pmu(void)
{
	struct device_node *dn = of_find_node_by_name(NULL, "via-pmu");

	if (!dn)
		return 0;
	of_node_put(dn);
	printk("WARNING ! Your machine is PMU-based but your kernel\n");
	printk("          wasn't compiled with CONFIG_ADB_PMU option !\n");
	return 0;
}
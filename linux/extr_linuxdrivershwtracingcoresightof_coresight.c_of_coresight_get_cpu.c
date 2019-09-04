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
 int of_cpu_node_to_id (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node const*,char*,int /*<<< orphan*/ ) ; 

int of_coresight_get_cpu(const struct device_node *node)
{
	int cpu;
	struct device_node *dn;

	dn = of_parse_phandle(node, "cpu", 0);
	/* Affinity defaults to CPU0 */
	if (!dn)
		return 0;
	cpu = of_cpu_node_to_id(dn);
	of_node_put(dn);

	/* Affinity to CPU0 if no cpu nodes are found */
	return (cpu < 0) ? 0 : cpu;
}
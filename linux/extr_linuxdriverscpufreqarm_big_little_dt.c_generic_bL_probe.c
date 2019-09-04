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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int bL_cpufreq_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_bL_ops ; 
 struct device_node* get_cpu_node_with_valid_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int generic_bL_probe(struct platform_device *pdev)
{
	struct device_node *np;

	np = get_cpu_node_with_valid_op(0);
	if (!np)
		return -ENODEV;

	of_node_put(np);
	return bL_cpufreq_register(&dt_bL_ops);
}
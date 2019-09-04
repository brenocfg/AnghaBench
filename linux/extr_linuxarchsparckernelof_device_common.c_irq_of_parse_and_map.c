#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_irqs; unsigned int* irqs; } ;
struct platform_device {TYPE_1__ archdata; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct platform_device* of_find_device_by_node (struct device_node*) ; 

unsigned int irq_of_parse_and_map(struct device_node *node, int index)
{
	struct platform_device *op = of_find_device_by_node(node);

	if (!op || index >= op->archdata.num_irqs)
		return 0;

	return op->archdata.irqs[index];
}
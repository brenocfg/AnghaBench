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
struct resource {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * resource; } ;
struct platform_device {int num_resources; TYPE_1__ archdata; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct resource*,int /*<<< orphan*/ *,int) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 

int of_address_to_resource(struct device_node *node, int index,
			   struct resource *r)
{
	struct platform_device *op = of_find_device_by_node(node);

	if (!op || index >= op->num_resources)
		return -EINVAL;

	memcpy(r, &op->archdata.resource[index], sizeof(*r));
	return 0;
}
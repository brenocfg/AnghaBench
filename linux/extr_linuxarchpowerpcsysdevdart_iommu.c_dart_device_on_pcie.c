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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool dart_device_on_pcie(struct device *dev)
{
	struct device_node *np = of_node_get(dev->of_node);

	while(np) {
		if (of_device_is_compatible(np, "U4-pcie") ||
		    of_device_is_compatible(np, "u4-pcie")) {
			of_node_put(np);
			return true;
		}
		np = of_get_next_parent(np);
	}
	return false;
}
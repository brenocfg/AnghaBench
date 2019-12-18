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
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static int xhci_rcar_is_gen2(struct device *dev)
{
	struct device_node *node = dev->of_node;

	return of_device_is_compatible(node, "renesas,xhci-r8a7790") ||
		of_device_is_compatible(node, "renesas,xhci-r8a7791") ||
		of_device_is_compatible(node, "renesas,xhci-r8a7793") ||
		of_device_is_compatible(node, "renesas,rcar-gen2-xhci");
}
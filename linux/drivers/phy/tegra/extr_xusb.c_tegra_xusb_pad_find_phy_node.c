#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct tegra_xusb_pad {TYPE_3__* soc; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_2__* lanes; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static struct device_node *
tegra_xusb_pad_find_phy_node(struct tegra_xusb_pad *pad, unsigned int index)
{
	struct device_node *np, *lanes;

	lanes = of_get_child_by_name(pad->dev.of_node, "lanes");
	if (!lanes)
		return NULL;

	np = of_get_child_by_name(lanes, pad->soc->lanes[index].name);
	of_node_put(lanes);

	return np;
}
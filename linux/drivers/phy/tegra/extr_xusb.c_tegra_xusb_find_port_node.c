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
struct tegra_xusb_padctl {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct device_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static struct device_node *
tegra_xusb_find_port_node(struct tegra_xusb_padctl *padctl, const char *type,
			  unsigned int index)
{
	struct device_node *ports, *np;
	char *name;

	ports = of_get_child_by_name(padctl->dev->of_node, "ports");
	if (!ports)
		return NULL;

	name = kasprintf(GFP_KERNEL, "%s-%u", type, index);
	if (!name) {
		of_node_put(ports);
		return ERR_PTR(-ENOMEM);
	}
	np = of_get_child_by_name(ports, name);
	kfree(name);
	of_node_put(ports);

	return np;
}
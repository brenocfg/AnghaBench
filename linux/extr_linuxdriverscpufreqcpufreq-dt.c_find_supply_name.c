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
struct property {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int id; int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static const char *find_supply_name(struct device *dev)
{
	struct device_node *np;
	struct property *pp;
	int cpu = dev->id;
	const char *name = NULL;

	np = of_node_get(dev->of_node);

	/* This must be valid for sure */
	if (WARN_ON(!np))
		return NULL;

	/* Try "cpu0" for older DTs */
	if (!cpu) {
		pp = of_find_property(np, "cpu0-supply", NULL);
		if (pp) {
			name = "cpu0";
			goto node_put;
		}
	}

	pp = of_find_property(np, "cpu-supply", NULL);
	if (pp) {
		name = "cpu";
		goto node_put;
	}

	dev_dbg(dev, "no regulator for cpu%d\n", cpu);
node_put:
	of_node_put(np);
	return name;
}
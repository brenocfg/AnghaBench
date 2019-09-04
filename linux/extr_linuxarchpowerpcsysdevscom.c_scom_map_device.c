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
typedef  int /*<<< orphan*/  u64 ;
struct device_node {struct device_node* parent; } ;
typedef  int /*<<< orphan*/ * scom_map_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,unsigned int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_read_number (int /*<<< orphan*/  const*,unsigned int) ; 
 struct device_node* scom_find_parent (struct device_node*) ; 
 int /*<<< orphan*/ * scom_map (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

scom_map_t scom_map_device(struct device_node *dev, int index)
{
	struct device_node *parent;
	unsigned int cells, size;
	const __be32 *prop, *sprop;
	u64 reg, cnt;
	scom_map_t ret;

	parent = scom_find_parent(dev);

	if (parent == NULL)
		return 0;

	/*
	 * We support "scom-reg" properties for adding scom registers
	 * to a random device-tree node with an explicit scom-parent
	 *
	 * We also support the simple "reg" property if the device is
	 * a direct child of a scom controller.
	 *
	 * In case both exist, "scom-reg" takes precedence.
	 */
	prop = of_get_property(dev, "scom-reg", &size);
	sprop = of_get_property(parent, "#scom-cells", NULL);
	if (!prop && parent == dev->parent) {
		prop = of_get_property(dev, "reg", &size);
		sprop = of_get_property(parent, "#address-cells", NULL);
	}
	if (!prop)
		return NULL;
	cells = sprop ? be32_to_cpup(sprop) : 1;
	size >>= 2;

	if (index >= (size / (2*cells)))
		return 0;

	reg = of_read_number(&prop[index * cells * 2], cells);
	cnt = of_read_number(&prop[index * cells * 2 + cells], cells);

	ret = scom_map(parent, reg, cnt);
	of_node_put(parent);

	return ret;
}
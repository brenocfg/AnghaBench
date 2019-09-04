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
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct property_set {struct device* dev; TYPE_1__ fwnode; struct property_entry const* properties; } ;
struct property_entry {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct property_set*) ; 
 int PTR_ERR (struct property_set*) ; 
 struct property_set* pset_copy_set (struct property_set*) ; 
 int /*<<< orphan*/  pset_fwnode_ops ; 
 int /*<<< orphan*/  set_secondary_fwnode (struct device*,TYPE_1__*) ; 

int device_add_properties(struct device *dev,
			  const struct property_entry *properties)
{
	struct property_set *p, pset;

	if (!properties)
		return -EINVAL;

	pset.properties = properties;

	p = pset_copy_set(&pset);
	if (IS_ERR(p))
		return PTR_ERR(p);

	p->fwnode.ops = &pset_fwnode_ops;
	set_secondary_fwnode(dev, &p->fwnode);
	p->dev = dev;
	return 0;
}
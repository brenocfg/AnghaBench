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
struct nd_region {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  dax_ida; } ;
struct device {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; int /*<<< orphan*/  groups; } ;
struct nd_pfn {scalar_t__ id; struct device dev; } ;
struct nd_dax {struct nd_pfn nd_pfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nd_dax*) ; 
 struct nd_dax* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_dax_attribute_groups ; 
 int /*<<< orphan*/  nd_dax_device_type ; 

__attribute__((used)) static struct nd_dax *nd_dax_alloc(struct nd_region *nd_region)
{
	struct nd_pfn *nd_pfn;
	struct nd_dax *nd_dax;
	struct device *dev;

	nd_dax = kzalloc(sizeof(*nd_dax), GFP_KERNEL);
	if (!nd_dax)
		return NULL;

	nd_pfn = &nd_dax->nd_pfn;
	nd_pfn->id = ida_simple_get(&nd_region->dax_ida, 0, 0, GFP_KERNEL);
	if (nd_pfn->id < 0) {
		kfree(nd_dax);
		return NULL;
	}

	dev = &nd_pfn->dev;
	dev_set_name(dev, "dax%d.%d", nd_region->id, nd_pfn->id);
	dev->groups = nd_dax_attribute_groups;
	dev->type = &nd_dax_device_type;
	dev->parent = &nd_region->dev;

	return nd_dax;
}
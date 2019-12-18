#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct nd_region {int /*<<< orphan*/  id; int /*<<< orphan*/  ns_ida; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  groups; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {struct resource res; TYPE_1__ common; } ;
struct nd_namespace_pmem {scalar_t__ id; TYPE_2__ nsio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_memory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nd_namespace_pmem*) ; 
 struct nd_namespace_pmem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namespace_pmem_device_type ; 
 int /*<<< orphan*/  nd_namespace_attribute_groups ; 
 int /*<<< orphan*/  nd_namespace_pmem_set_resource (struct nd_region*,struct nd_namespace_pmem*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *nd_namespace_pmem_create(struct nd_region *nd_region)
{
	struct nd_namespace_pmem *nspm;
	struct resource *res;
	struct device *dev;

	if (!is_memory(&nd_region->dev))
		return NULL;

	nspm = kzalloc(sizeof(*nspm), GFP_KERNEL);
	if (!nspm)
		return NULL;

	dev = &nspm->nsio.common.dev;
	dev->type = &namespace_pmem_device_type;
	dev->parent = &nd_region->dev;
	res = &nspm->nsio.res;
	res->name = dev_name(&nd_region->dev);
	res->flags = IORESOURCE_MEM;

	nspm->id = ida_simple_get(&nd_region->ns_ida, 0, 0, GFP_KERNEL);
	if (nspm->id < 0) {
		kfree(nspm);
		return NULL;
	}
	dev_set_name(dev, "namespace%d.%d", nd_region->id, nspm->id);
	dev->groups = nd_namespace_attribute_groups;
	nd_namespace_pmem_set_resource(nd_region, nspm, 0);

	return dev;
}
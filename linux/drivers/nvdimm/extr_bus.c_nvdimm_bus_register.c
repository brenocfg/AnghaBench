#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvdimm_bus_descriptor {int /*<<< orphan*/  of_node; int /*<<< orphan*/  attr_groups; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * bus; int /*<<< orphan*/  groups; int /*<<< orphan*/  release; struct device* parent; } ;
struct nvdimm_bus {scalar_t__ id; TYPE_1__ dev; struct nvdimm_bus_descriptor* nd_desc; int /*<<< orphan*/  badrange; int /*<<< orphan*/  reconfig_mutex; int /*<<< orphan*/  wait; int /*<<< orphan*/  mapping_list; int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  badrange_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,scalar_t__) ; 
 int device_register (TYPE_1__*) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvdimm_bus*) ; 
 struct nvdimm_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_ida ; 
 int /*<<< orphan*/  nvdimm_bus_release ; 
 int /*<<< orphan*/  nvdimm_bus_type ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

struct nvdimm_bus *nvdimm_bus_register(struct device *parent,
		struct nvdimm_bus_descriptor *nd_desc)
{
	struct nvdimm_bus *nvdimm_bus;
	int rc;

	nvdimm_bus = kzalloc(sizeof(*nvdimm_bus), GFP_KERNEL);
	if (!nvdimm_bus)
		return NULL;
	INIT_LIST_HEAD(&nvdimm_bus->list);
	INIT_LIST_HEAD(&nvdimm_bus->mapping_list);
	init_waitqueue_head(&nvdimm_bus->wait);
	nvdimm_bus->id = ida_simple_get(&nd_ida, 0, 0, GFP_KERNEL);
	if (nvdimm_bus->id < 0) {
		kfree(nvdimm_bus);
		return NULL;
	}
	mutex_init(&nvdimm_bus->reconfig_mutex);
	badrange_init(&nvdimm_bus->badrange);
	nvdimm_bus->nd_desc = nd_desc;
	nvdimm_bus->dev.parent = parent;
	nvdimm_bus->dev.release = nvdimm_bus_release;
	nvdimm_bus->dev.groups = nd_desc->attr_groups;
	nvdimm_bus->dev.bus = &nvdimm_bus_type;
	nvdimm_bus->dev.of_node = nd_desc->of_node;
	dev_set_name(&nvdimm_bus->dev, "ndbus%d", nvdimm_bus->id);
	rc = device_register(&nvdimm_bus->dev);
	if (rc) {
		dev_dbg(&nvdimm_bus->dev, "registration failed: %d\n", rc);
		goto err;
	}

	return nvdimm_bus;
 err:
	put_device(&nvdimm_bus->dev);
	return NULL;
}
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
struct nd_region {struct device* ns_seed; int /*<<< orphan*/  id; int /*<<< orphan*/  ns_ida; int /*<<< orphan*/  dev; } ;
struct nd_namespace_pmem {int id; } ;
struct nd_namespace_blk {int id; } ;
struct device {int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  ND_DEVICE_NAMESPACE_BLK 130 
#define  ND_DEVICE_NAMESPACE_IO 129 
#define  ND_DEVICE_NAMESPACE_PMEM 128 
 struct device** create_namespace_io (struct nd_region*) ; 
 struct device** create_namespaces (struct nd_region*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_active_labels (struct nd_region*) ; 
 int /*<<< orphan*/  kfree (struct device**) ; 
 int /*<<< orphan*/  nd_device_register (struct device*) ; 
 int /*<<< orphan*/  nd_namespace_attribute_groups ; 
 int nd_region_to_nstype (struct nd_region*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 

int nd_region_register_namespaces(struct nd_region *nd_region, int *err)
{
	struct device **devs = NULL;
	int i, rc = 0, type;

	*err = 0;
	nvdimm_bus_lock(&nd_region->dev);
	rc = init_active_labels(nd_region);
	if (rc) {
		nvdimm_bus_unlock(&nd_region->dev);
		return rc;
	}

	type = nd_region_to_nstype(nd_region);
	switch (type) {
	case ND_DEVICE_NAMESPACE_IO:
		devs = create_namespace_io(nd_region);
		break;
	case ND_DEVICE_NAMESPACE_PMEM:
	case ND_DEVICE_NAMESPACE_BLK:
		devs = create_namespaces(nd_region);
		break;
	default:
		break;
	}
	nvdimm_bus_unlock(&nd_region->dev);

	if (!devs)
		return -ENODEV;

	for (i = 0; devs[i]; i++) {
		struct device *dev = devs[i];
		int id;

		if (type == ND_DEVICE_NAMESPACE_BLK) {
			struct nd_namespace_blk *nsblk;

			nsblk = to_nd_namespace_blk(dev);
			id = ida_simple_get(&nd_region->ns_ida, 0, 0,
					GFP_KERNEL);
			nsblk->id = id;
		} else if (type == ND_DEVICE_NAMESPACE_PMEM) {
			struct nd_namespace_pmem *nspm;

			nspm = to_nd_namespace_pmem(dev);
			id = ida_simple_get(&nd_region->ns_ida, 0, 0,
					GFP_KERNEL);
			nspm->id = id;
		} else
			id = i;

		if (id < 0)
			break;
		dev_set_name(dev, "namespace%d.%d", nd_region->id, id);
		dev->groups = nd_namespace_attribute_groups;
		nd_device_register(dev);
	}
	if (i)
		nd_region->ns_seed = devs[0];

	if (devs[i]) {
		int j;

		for (j = i; devs[j]; j++) {
			struct device *dev = devs[j];

			device_initialize(dev);
			put_device(dev);
		}
		*err = j - i;
		/*
		 * All of the namespaces we tried to register failed, so
		 * fail region activation.
		 */
		if (*err == 0)
			rc = -ENODEV;
	}
	kfree(devs);

	if (rc == -ENODEV)
		return rc;

	return i;
}
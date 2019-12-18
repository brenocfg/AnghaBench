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
struct nvdimm_bus {int /*<<< orphan*/  nd_desc; int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvdimm_bus_create_ndctl (struct nvdimm_bus*) ; 
 int /*<<< orphan*/  nvdimm_bus_list ; 
 int /*<<< orphan*/  nvdimm_bus_list_mutex ; 
 struct nvdimm_bus* to_nvdimm_bus (struct device*) ; 

__attribute__((used)) static int nd_bus_probe(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	int rc;

	rc = nvdimm_bus_create_ndctl(nvdimm_bus);
	if (rc)
		return rc;

	mutex_lock(&nvdimm_bus_list_mutex);
	list_add_tail(&nvdimm_bus->list, &nvdimm_bus_list);
	mutex_unlock(&nvdimm_bus_list_mutex);

	/* enable bus provider attributes to look up their local context */
	dev_set_drvdata(dev, nvdimm_bus->nd_desc);

	return 0;
}
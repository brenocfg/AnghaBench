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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct nvdimm_bus_descriptor {char* provider_name; int /*<<< orphan*/  module; int /*<<< orphan*/  attr_groups; } ;
struct nvdimm_bus {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IORES_DESC_PERSISTENT_MEMORY_LEGACY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  e820_pmem_attribute_groups ; 
 int /*<<< orphan*/  e820_register_one ; 
 struct nvdimm_bus* nvdimm_bus_register (struct device*,struct nvdimm_bus_descriptor*) ; 
 int /*<<< orphan*/  nvdimm_bus_unregister (struct nvdimm_bus*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nvdimm_bus*) ; 
 int walk_iomem_res_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nvdimm_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e820_pmem_probe(struct platform_device *pdev)
{
	static struct nvdimm_bus_descriptor nd_desc;
	struct device *dev = &pdev->dev;
	struct nvdimm_bus *nvdimm_bus;
	int rc = -ENXIO;

	nd_desc.attr_groups = e820_pmem_attribute_groups;
	nd_desc.provider_name = "e820";
	nd_desc.module = THIS_MODULE;
	nvdimm_bus = nvdimm_bus_register(dev, &nd_desc);
	if (!nvdimm_bus)
		goto err;
	platform_set_drvdata(pdev, nvdimm_bus);

	rc = walk_iomem_res_desc(IORES_DESC_PERSISTENT_MEMORY_LEGACY,
			IORESOURCE_MEM, 0, -1, nvdimm_bus, e820_register_one);
	if (rc)
		goto err;
	return 0;
err:
	nvdimm_bus_unregister(nvdimm_bus);
	dev_err(dev, "failed to register legacy persistent memory ranges\n");
	return rc;
}
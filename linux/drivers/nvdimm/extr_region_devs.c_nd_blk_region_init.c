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
struct nvdimm_bus {int dummy; } ;
struct device {int dummy; } ;
struct nd_region {int ndr_mappings; struct device dev; } ;
struct TYPE_2__ {int (* enable ) (struct nvdimm_bus*,struct device*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  is_nd_blk (struct device*) ; 
 int stub1 (struct nvdimm_bus*,struct device*) ; 
 TYPE_1__* to_nd_blk_region (struct device*) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

int nd_blk_region_init(struct nd_region *nd_region)
{
	struct device *dev = &nd_region->dev;
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	if (!is_nd_blk(dev))
		return 0;

	if (nd_region->ndr_mappings < 1) {
		dev_dbg(dev, "invalid BLK region\n");
		return -ENXIO;
	}

	return to_nd_blk_region(dev)->enable(nvdimm_bus, dev);
}
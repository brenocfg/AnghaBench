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
typedef  size_t u16 ;
struct nvdimm {int /*<<< orphan*/  dev; } ;
struct nd_region {size_t ndr_mappings; int /*<<< orphan*/  id; int /*<<< orphan*/  lane; struct nd_mapping* mapping; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_nd_blk (struct device*) ; 
 int /*<<< orphan*/  kfree (struct nd_region*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  region_ida ; 
 struct nd_region* to_nd_blk_region (struct device*) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static void nd_region_release(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev);
	u16 i;

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm *nvdimm = nd_mapping->nvdimm;

		put_device(&nvdimm->dev);
	}
	free_percpu(nd_region->lane);
	ida_simple_remove(&region_ida, nd_region->id);
	if (is_nd_blk(dev))
		kfree(to_nd_blk_region(dev));
	else
		kfree(nd_region);
}
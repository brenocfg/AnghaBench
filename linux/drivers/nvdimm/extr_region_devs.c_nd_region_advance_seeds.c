#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nd_region {struct device* ns_seed; struct device* dax_seed; struct device* pfn_seed; struct device* btt_seed; } ;
struct nd_pfn {TYPE_2__* ndns; } ;
struct TYPE_8__ {TYPE_3__* ndns; } ;
struct nd_dax {TYPE_4__ nd_pfn; } ;
struct nd_btt {TYPE_1__* ndns; } ;
struct device {int dummy; } ;
struct TYPE_7__ {struct device dev; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 int /*<<< orphan*/  nd_region_create_btt_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_create_dax_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_create_ns_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_create_pfn_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_dax* to_nd_dax (struct device*) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 

void nd_region_advance_seeds(struct nd_region *nd_region, struct device *dev)
{
	nvdimm_bus_lock(dev);
	if (nd_region->ns_seed == dev) {
		nd_region_create_ns_seed(nd_region);
	} else if (is_nd_btt(dev)) {
		struct nd_btt *nd_btt = to_nd_btt(dev);

		if (nd_region->btt_seed == dev)
			nd_region_create_btt_seed(nd_region);
		if (nd_region->ns_seed == &nd_btt->ndns->dev)
			nd_region_create_ns_seed(nd_region);
	} else if (is_nd_pfn(dev)) {
		struct nd_pfn *nd_pfn = to_nd_pfn(dev);

		if (nd_region->pfn_seed == dev)
			nd_region_create_pfn_seed(nd_region);
		if (nd_region->ns_seed == &nd_pfn->ndns->dev)
			nd_region_create_ns_seed(nd_region);
	} else if (is_nd_dax(dev)) {
		struct nd_dax *nd_dax = to_nd_dax(dev);

		if (nd_region->dax_seed == dev)
			nd_region_create_dax_seed(nd_region);
		if (nd_region->ns_seed == &nd_dax->nd_pfn.ndns->dev)
			nd_region_create_ns_seed(nd_region);
	}
	nvdimm_bus_unlock(dev);
}
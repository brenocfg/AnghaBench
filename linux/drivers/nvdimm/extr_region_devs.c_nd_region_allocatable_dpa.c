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
struct nd_region {int ndr_mappings; int /*<<< orphan*/  dev; struct nd_mapping* mapping; } ;
struct nd_mapping {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int PHYS_ADDR_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ is_nd_blk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nd_blk_available_dpa (struct nd_region*) ; 
 int /*<<< orphan*/  nd_pmem_max_contiguous_dpa (struct nd_region*,struct nd_mapping*) ; 

resource_size_t nd_region_allocatable_dpa(struct nd_region *nd_region)
{
	resource_size_t available = 0;
	int i;

	if (is_memory(&nd_region->dev))
		available = PHYS_ADDR_MAX;

	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));
	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];

		if (is_memory(&nd_region->dev))
			available = min(available,
					nd_pmem_max_contiguous_dpa(nd_region,
								   nd_mapping));
		else if (is_nd_blk(&nd_region->dev))
			available += nd_blk_available_dpa(nd_region);
	}
	if (is_memory(&nd_region->dev))
		return available * nd_region->ndr_mappings;
	return available;
}
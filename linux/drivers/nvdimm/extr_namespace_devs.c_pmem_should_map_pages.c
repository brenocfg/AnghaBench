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
struct nd_region {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct nd_namespace_io {TYPE_1__ res; } ;
struct nd_namespace_common {scalar_t__ force_raw; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ ARCH_MEMREMAP_PMEM ; 
 int /*<<< orphan*/  CONFIG_ZONE_DEVICE ; 
 int /*<<< orphan*/  IORESOURCE_SYSTEM_RAM ; 
 int /*<<< orphan*/  IORES_DESC_NONE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ MEMREMAP_WB ; 
 int /*<<< orphan*/  ND_REGION_PAGEMAP ; 
 scalar_t__ REGION_MIXED ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 scalar_t__ region_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nd_namespace_io* to_nd_namespace_io (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 
 struct nd_namespace_common* to_ndns (struct device*) ; 

bool pmem_should_map_pages(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct nd_namespace_common *ndns = to_ndns(dev);
	struct nd_namespace_io *nsio;

	if (!IS_ENABLED(CONFIG_ZONE_DEVICE))
		return false;

	if (!test_bit(ND_REGION_PAGEMAP, &nd_region->flags))
		return false;

	if (is_nd_pfn(dev) || is_nd_btt(dev))
		return false;

	if (ndns->force_raw)
		return false;

	nsio = to_nd_namespace_io(dev);
	if (region_intersects(nsio->res.start, resource_size(&nsio->res),
				IORESOURCE_SYSTEM_RAM,
				IORES_DESC_NONE) == REGION_MIXED)
		return false;

	return ARCH_MEMREMAP_PMEM == MEMREMAP_WB;
}
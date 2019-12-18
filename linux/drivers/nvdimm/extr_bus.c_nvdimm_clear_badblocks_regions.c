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
typedef  int /*<<< orphan*/  u64 ;
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct clear_badblocks_context {int /*<<< orphan*/  cleared; int /*<<< orphan*/  phys; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct clear_badblocks_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_clear_badblocks_region ; 

__attribute__((used)) static void nvdimm_clear_badblocks_regions(struct nvdimm_bus *nvdimm_bus,
		phys_addr_t phys, u64 cleared)
{
	struct clear_badblocks_context ctx = {
		.phys = phys,
		.cleared = cleared,
	};

	device_for_each_child(&nvdimm_bus->dev, &ctx,
			nvdimm_clear_badblocks_region);
}
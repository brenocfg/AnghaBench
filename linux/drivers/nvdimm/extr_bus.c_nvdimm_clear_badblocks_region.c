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
struct nd_region {scalar_t__ ndr_start; scalar_t__ ndr_size; scalar_t__ bb_state; int /*<<< orphan*/  bb; } ;
struct device {int dummy; } ;
struct clear_badblocks_context {scalar_t__ phys; int cleared; } ;
typedef  int sector_t ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_clear (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  is_memory (struct device*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent (scalar_t__) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static int nvdimm_clear_badblocks_region(struct device *dev, void *data)
{
	struct clear_badblocks_context *ctx = data;
	struct nd_region *nd_region;
	resource_size_t ndr_end;
	sector_t sector;

	/* make sure device is a region */
	if (!is_memory(dev))
		return 0;

	nd_region = to_nd_region(dev);
	ndr_end = nd_region->ndr_start + nd_region->ndr_size - 1;

	/* make sure we are in the region */
	if (ctx->phys < nd_region->ndr_start
			|| (ctx->phys + ctx->cleared) > ndr_end)
		return 0;

	sector = (ctx->phys - nd_region->ndr_start) / 512;
	badblocks_clear(&nd_region->bb, sector, ctx->cleared / 512);

	if (nd_region->bb_state)
		sysfs_notify_dirent(nd_region->bb_state);

	return 0;
}
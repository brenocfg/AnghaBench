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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct nvdimm_drvdata {int dummy; } ;
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct nd_region {int /*<<< orphan*/  dev; struct nd_mapping* mapping; } ;
struct nd_mapping {int /*<<< orphan*/  size; } ;
struct nd_label_id {int /*<<< orphan*/  id; } ;
struct blk_alloc_info {struct resource* res; int /*<<< orphan*/  available; struct nd_mapping* nd_mapping; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  alias_dpa_busy ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct blk_alloc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_nd_blk (int /*<<< orphan*/ *) ; 
 scalar_t__ resource_size (struct resource*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void space_valid(struct nd_region *nd_region, struct nvdimm_drvdata *ndd,
		struct nd_label_id *label_id, struct resource *prev,
		struct resource *next, struct resource *exist,
		resource_size_t n, struct resource *valid)
{
	bool is_reserve = strcmp(label_id->id, "pmem-reserve") == 0;
	bool is_pmem = strncmp(label_id->id, "pmem", 4) == 0;

	if (valid->start >= valid->end)
		goto invalid;

	if (is_reserve)
		return;

	if (!is_pmem) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[0];
		struct nvdimm_bus *nvdimm_bus;
		struct blk_alloc_info info = {
			.nd_mapping = nd_mapping,
			.available = nd_mapping->size,
			.res = valid,
		};

		WARN_ON(!is_nd_blk(&nd_region->dev));
		nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);
		device_for_each_child(&nvdimm_bus->dev, &info, alias_dpa_busy);
		return;
	}

	/* allocation needs to be contiguous, so this is all or nothing */
	if (resource_size(valid) < n)
		goto invalid;

	/* we've got all the space we need and no existing allocation */
	if (!exist)
		return;

	/* allocation needs to be contiguous with the existing namespace */
	if (valid->start == exist->end + 1
			|| valid->end == exist->start - 1)
		return;

 invalid:
	/* truncate @valid size to 0 */
	valid->end = valid->start - 1;
}
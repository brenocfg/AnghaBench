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
struct nvdimm {int num_flush; int /*<<< orphan*/  flags; } ;
struct nd_region_data {int /*<<< orphan*/  hints_shift; } ;
struct device {int dummy; } ;
struct nd_region {int ndr_mappings; struct device dev; struct nd_mapping* mapping; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NDD_SECURITY_OVERWRITE ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct nd_region_data*) ; 
 struct nd_region_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int min_not_zero (int,int) ; 
 scalar_t__ ndrd_get_flush_wpq (struct nd_region_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndrd_set_flush_wpq (struct nd_region_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int nvdimm_map_flush (struct device*,struct nvdimm*,int,struct nd_region_data*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nd_region_activate(struct nd_region *nd_region)
{
	int i, j, num_flush = 0;
	struct nd_region_data *ndrd;
	struct device *dev = &nd_region->dev;
	size_t flush_data_size = sizeof(void *);

	nvdimm_bus_lock(&nd_region->dev);
	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm *nvdimm = nd_mapping->nvdimm;

		if (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) {
			nvdimm_bus_unlock(&nd_region->dev);
			return -EBUSY;
		}

		/* at least one null hint slot per-dimm for the "no-hint" case */
		flush_data_size += sizeof(void *);
		num_flush = min_not_zero(num_flush, nvdimm->num_flush);
		if (!nvdimm->num_flush)
			continue;
		flush_data_size += nvdimm->num_flush * sizeof(void *);
	}
	nvdimm_bus_unlock(&nd_region->dev);

	ndrd = devm_kzalloc(dev, sizeof(*ndrd) + flush_data_size, GFP_KERNEL);
	if (!ndrd)
		return -ENOMEM;
	dev_set_drvdata(dev, ndrd);

	if (!num_flush)
		return 0;

	ndrd->hints_shift = ilog2(num_flush);
	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm *nvdimm = nd_mapping->nvdimm;
		int rc = nvdimm_map_flush(&nd_region->dev, nvdimm, i, ndrd);

		if (rc)
			return rc;
	}

	/*
	 * Clear out entries that are duplicates. This should prevent the
	 * extra flushings.
	 */
	for (i = 0; i < nd_region->ndr_mappings - 1; i++) {
		/* ignore if NULL already */
		if (!ndrd_get_flush_wpq(ndrd, i, 0))
			continue;

		for (j = i + 1; j < nd_region->ndr_mappings; j++)
			if (ndrd_get_flush_wpq(ndrd, i, 0) ==
			    ndrd_get_flush_wpq(ndrd, j, 0))
				ndrd_set_flush_wpq(ndrd, j, 0, NULL);
	}

	return 0;
}
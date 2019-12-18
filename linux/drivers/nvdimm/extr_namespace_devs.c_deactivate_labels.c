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
struct nvdimm_drvdata {int dummy; } ;
struct nvdimm {int /*<<< orphan*/  busy; } ;
struct nd_region {int ndr_mappings; struct nd_mapping* mapping; } ;
struct nd_mapping {struct nvdimm_drvdata* ndd; int /*<<< orphan*/  lock; struct nvdimm* nvdimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_mapping_free_labels (struct nd_mapping*) ; 
 int /*<<< orphan*/  put_ndd (struct nvdimm_drvdata*) ; 

__attribute__((used)) static void deactivate_labels(void *region)
{
	struct nd_region *nd_region = region;
	int i;

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm_drvdata *ndd = nd_mapping->ndd;
		struct nvdimm *nvdimm = nd_mapping->nvdimm;

		mutex_lock(&nd_mapping->lock);
		nd_mapping_free_labels(nd_mapping);
		mutex_unlock(&nd_mapping->lock);

		put_ndd(ndd);
		nd_mapping->ndd = NULL;
		if (ndd)
			atomic_dec(&nvdimm->busy);
	}
}
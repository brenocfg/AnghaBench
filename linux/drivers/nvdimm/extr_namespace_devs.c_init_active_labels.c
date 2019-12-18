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
typedef  int /*<<< orphan*/  u32 ;
struct nvdimm_drvdata {int /*<<< orphan*/  dev; } ;
struct nvdimm {int /*<<< orphan*/  flags; int /*<<< orphan*/  busy; int /*<<< orphan*/  dev; } ;
struct nd_region {int ndr_mappings; int /*<<< orphan*/  dev; struct nd_mapping* mapping; } ;
struct nd_namespace_label {int /*<<< orphan*/  flags; } ;
struct nd_mapping {int /*<<< orphan*/  lock; int /*<<< orphan*/  labels; struct nvdimm_drvdata* ndd; struct nvdimm* nvdimm; } ;
struct nd_label_ent {int /*<<< orphan*/  list; struct nd_namespace_label* label; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NDD_ALIASING ; 
 int /*<<< orphan*/  NDD_LOCKED ; 
 int /*<<< orphan*/  NDD_NOBLK ; 
 int /*<<< orphan*/  NSLABEL_FLAG_LOCAL ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deactivate_labels (struct nd_region*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct nd_region*),struct nd_region*) ; 
 int /*<<< orphan*/  get_ndd (struct nvdimm_drvdata*) ; 
 struct nd_label_ent* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nd_namespace_label* nd_label_active (struct nvdimm_drvdata*,int) ; 
 int nd_label_active_count (struct nvdimm_drvdata*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvdimm_drvdata* to_ndd (struct nd_mapping*) ; 

__attribute__((used)) static int init_active_labels(struct nd_region *nd_region)
{
	int i;

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		struct nvdimm *nvdimm = nd_mapping->nvdimm;
		struct nd_label_ent *label_ent;
		int count, j;

		/*
		 * If the dimm is disabled then we may need to prevent
		 * the region from being activated.
		 */
		if (!ndd) {
			if (test_bit(NDD_LOCKED, &nvdimm->flags))
				/* fail, label data may be unreadable */;
			else if (test_bit(NDD_ALIASING, &nvdimm->flags))
				/* fail, labels needed to disambiguate dpa */;
			else
				return 0;

			dev_err(&nd_region->dev, "%s: is %s, failing probe\n",
					dev_name(&nd_mapping->nvdimm->dev),
					test_bit(NDD_LOCKED, &nvdimm->flags)
					? "locked" : "disabled");
			return -ENXIO;
		}
		nd_mapping->ndd = ndd;
		atomic_inc(&nvdimm->busy);
		get_ndd(ndd);

		count = nd_label_active_count(ndd);
		dev_dbg(ndd->dev, "count: %d\n", count);
		if (!count)
			continue;
		for (j = 0; j < count; j++) {
			struct nd_namespace_label *label;

			label_ent = kzalloc(sizeof(*label_ent), GFP_KERNEL);
			if (!label_ent)
				break;
			label = nd_label_active(ndd, j);
			if (test_bit(NDD_NOBLK, &nvdimm->flags)) {
				u32 flags = __le32_to_cpu(label->flags);

				flags &= ~NSLABEL_FLAG_LOCAL;
				label->flags = __cpu_to_le32(flags);
			}
			label_ent->label = label;

			mutex_lock(&nd_mapping->lock);
			list_add_tail(&label_ent->list, &nd_mapping->labels);
			mutex_unlock(&nd_mapping->lock);
		}

		if (j < count)
			break;
	}

	if (i < nd_region->ndr_mappings) {
		deactivate_labels(nd_region);
		return -ENOMEM;
	}

	return devm_add_action_or_reset(&nd_region->dev, deactivate_labels,
			nd_region);
}
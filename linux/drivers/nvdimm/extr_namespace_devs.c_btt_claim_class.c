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
struct nvdimm_drvdata {int /*<<< orphan*/  ns_current; } ;
struct nd_region {int ndr_mappings; struct nd_mapping* mapping; } ;
struct nd_namespace_index {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct nd_mapping {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENXIO ; 
 int NVDIMM_CCLASS_BTT ; 
 int NVDIMM_CCLASS_BTT2 ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct nd_namespace_index* to_namespace_index (struct nvdimm_drvdata*,int /*<<< orphan*/ ) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 
 struct nvdimm_drvdata* to_ndd (struct nd_mapping*) ; 

__attribute__((used)) static int btt_claim_class(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	int i, loop_bitmask = 0;

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		struct nd_namespace_index *nsindex;

		/*
		 * If any of the DIMMs do not support labels the only
		 * possible BTT format is v1.
		 */
		if (!ndd) {
			loop_bitmask = 0;
			break;
		}

		nsindex = to_namespace_index(ndd, ndd->ns_current);
		if (nsindex == NULL)
			loop_bitmask |= 1;
		else {
			/* check whether existing labels are v1.1 or v1.2 */
			if (__le16_to_cpu(nsindex->major) == 1
					&& __le16_to_cpu(nsindex->minor) == 1)
				loop_bitmask |= 2;
			else
				loop_bitmask |= 4;
		}
	}
	/*
	 * If nsindex is null loop_bitmask's bit 0 will be set, and if an index
	 * block is found, a v1.1 label for any mapping will set bit 1, and a
	 * v1.2 label will set bit 2.
	 *
	 * At the end of the loop, at most one of the three bits must be set.
	 * If multiple bits were set, it means the different mappings disagree
	 * about their labels, and this must be cleaned up first.
	 *
	 * If all the label index blocks are found to agree, nsindex of NULL
	 * implies labels haven't been initialized yet, and when they will,
	 * they will be of the 1.2 format, so we can assume BTT2.0
	 *
	 * If 1.1 labels are found, we enforce BTT1.1, and if 1.2 labels are
	 * found, we enforce BTT2.0
	 *
	 * If the loop was never entered, default to BTT1.1 (legacy namespaces)
	 */
	switch (loop_bitmask) {
	case 0:
	case 2:
		return NVDIMM_CCLASS_BTT;
	case 1:
	case 4:
		return NVDIMM_CCLASS_BTT2;
	default:
		return -ENXIO;
	}
}
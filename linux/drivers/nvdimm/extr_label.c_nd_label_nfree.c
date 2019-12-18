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
struct nd_namespace_index {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_weight (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_num_label_slots (struct nvdimm_drvdata*) ; 
 int /*<<< orphan*/  preamble_next (struct nvdimm_drvdata*,struct nd_namespace_index**,unsigned long**,int /*<<< orphan*/ *) ; 

u32 nd_label_nfree(struct nvdimm_drvdata *ndd)
{
	struct nd_namespace_index *nsindex;
	unsigned long *free;
	u32 nslot;

	WARN_ON(!is_nvdimm_bus_locked(ndd->dev));

	if (!preamble_next(ndd, &nsindex, &free, &nslot))
		return nvdimm_num_label_slots(ndd);

	return bitmap_weight(free, nslot);
}
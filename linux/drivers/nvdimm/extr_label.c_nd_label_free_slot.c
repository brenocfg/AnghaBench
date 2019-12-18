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
typedef  scalar_t__ u32 ;
struct nvdimm_drvdata {int /*<<< orphan*/  dev; } ;
struct nd_namespace_index {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preamble_next (struct nvdimm_drvdata*,struct nd_namespace_index**,unsigned long**,scalar_t__*) ; 
 int /*<<< orphan*/  test_and_set_bit_le (scalar_t__,unsigned long*) ; 

bool nd_label_free_slot(struct nvdimm_drvdata *ndd, u32 slot)
{
	struct nd_namespace_index *nsindex;
	unsigned long *free;
	u32 nslot;

	if (!preamble_next(ndd, &nsindex, &free, &nslot))
		return false;

	WARN_ON(!is_nvdimm_bus_locked(ndd->dev));

	if (slot < nslot)
		return !test_and_set_bit_le(slot, free);
	return false;
}
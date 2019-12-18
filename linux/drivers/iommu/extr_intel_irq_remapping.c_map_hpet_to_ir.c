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
typedef  scalar_t__ u8 ;
struct intel_iommu {int dummy; } ;
struct TYPE_2__ {scalar_t__ id; struct intel_iommu* iommu; } ;

/* Variables and functions */
 int MAX_HPET_TBS ; 
 TYPE_1__* ir_hpet ; 

__attribute__((used)) static struct intel_iommu *map_hpet_to_ir(u8 hpet_id)
{
	int i;

	for (i = 0; i < MAX_HPET_TBS; i++)
		if (ir_hpet[i].id == hpet_id && ir_hpet[i].iommu)
			return ir_hpet[i].iommu;
	return NULL;
}
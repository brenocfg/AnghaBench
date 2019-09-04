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
struct intel_iommu {int dummy; } ;
struct TYPE_2__ {int id; struct intel_iommu* iommu; } ;

/* Variables and functions */
 int MAX_IO_APICS ; 
 TYPE_1__* ir_ioapic ; 

__attribute__((used)) static struct intel_iommu *map_ioapic_to_ir(int apic)
{
	int i;

	for (i = 0; i < MAX_IO_APICS; i++)
		if (ir_ioapic[i].id == apic && ir_ioapic[i].iommu)
			return ir_ioapic[i].iommu;
	return NULL;
}
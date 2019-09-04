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
typedef  int u16 ;
struct irte {int dummy; } ;
struct TYPE_2__ {int id; int bus; int devfn; scalar_t__ iommu; } ;

/* Variables and functions */
 int MAX_IO_APICS ; 
 int /*<<< orphan*/  SQ_ALL_16 ; 
 int /*<<< orphan*/  SVT_VERIFY_SID_SQ ; 
 int /*<<< orphan*/  dmar_global_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* ir_ioapic ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  set_irte_sid (struct irte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_ioapic_sid(struct irte *irte, int apic)
{
	int i;
	u16 sid = 0;

	if (!irte)
		return -1;

	down_read(&dmar_global_lock);
	for (i = 0; i < MAX_IO_APICS; i++) {
		if (ir_ioapic[i].iommu && ir_ioapic[i].id == apic) {
			sid = (ir_ioapic[i].bus << 8) | ir_ioapic[i].devfn;
			break;
		}
	}
	up_read(&dmar_global_lock);

	if (sid == 0) {
		pr_warn("Failed to set source-id of IOAPIC (%d)\n", apic);
		return -1;
	}

	set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16, sid);

	return 0;
}
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
typedef  int u16 ;
struct irte {int dummy; } ;
struct TYPE_2__ {scalar_t__ id; int bus; int devfn; scalar_t__ iommu; } ;

/* Variables and functions */
 int MAX_HPET_TBS ; 
 int /*<<< orphan*/  SQ_13_IGNORE_3 ; 
 int /*<<< orphan*/  SVT_VERIFY_SID_SQ ; 
 int /*<<< orphan*/  dmar_global_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* ir_hpet ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  set_irte_sid (struct irte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_hpet_sid(struct irte *irte, u8 id)
{
	int i;
	u16 sid = 0;

	if (!irte)
		return -1;

	down_read(&dmar_global_lock);
	for (i = 0; i < MAX_HPET_TBS; i++) {
		if (ir_hpet[i].iommu && ir_hpet[i].id == id) {
			sid = (ir_hpet[i].bus << 8) | ir_hpet[i].devfn;
			break;
		}
	}
	up_read(&dmar_global_lock);

	if (sid == 0) {
		pr_warn("Failed to set source-id of HPET block (%d)\n", id);
		return -1;
	}

	/*
	 * Should really use SQ_ALL_16. Some platforms are broken.
	 * While we figure out the right quirks for these broken platforms, use
	 * SQ_13_IGNORE_3 for now.
	 */
	set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_13_IGNORE_3, sid);

	return 0;
}
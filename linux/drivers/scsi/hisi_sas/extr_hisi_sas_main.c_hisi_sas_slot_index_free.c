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
struct hisi_hba {int /*<<< orphan*/  lock; TYPE_1__* hw; } ;
struct TYPE_2__ {scalar_t__ slot_index_alloc; } ;

/* Variables and functions */
 int HISI_SAS_UNRESERVED_IPTT ; 
 int /*<<< orphan*/  hisi_sas_slot_index_clear (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hisi_sas_slot_index_free(struct hisi_hba *hisi_hba, int slot_idx)
{
	unsigned long flags;

	if (hisi_hba->hw->slot_index_alloc ||
	    slot_idx >= HISI_SAS_UNRESERVED_IPTT) {
		spin_lock_irqsave(&hisi_hba->lock, flags);
		hisi_sas_slot_index_clear(hisi_hba, slot_idx);
		spin_unlock_irqrestore(&hisi_hba->lock, flags);
	}
}
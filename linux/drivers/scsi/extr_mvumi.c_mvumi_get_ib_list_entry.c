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
struct mvumi_hba {unsigned int ib_cur_slot; unsigned int list_num_io; int hba_capability; unsigned int ib_max_size; int /*<<< orphan*/  fw_outstanding; void* ib_list; TYPE_1__* regs; } ;
struct mvumi_dyn_list_entry {int dummy; } ;
struct TYPE_2__ {unsigned int cl_slot_num_mask; unsigned int cl_pointer_toggle; } ;

/* Variables and functions */
 int HS_CAPABILITY_SUPPORT_DYN_SRC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvumi_get_ib_list_entry(struct mvumi_hba *mhba, void **ib_entry)
{
	unsigned int cur_ib_entry;

	cur_ib_entry = mhba->ib_cur_slot & mhba->regs->cl_slot_num_mask;
	cur_ib_entry++;
	if (cur_ib_entry >= mhba->list_num_io) {
		cur_ib_entry -= mhba->list_num_io;
		mhba->ib_cur_slot ^= mhba->regs->cl_pointer_toggle;
	}
	mhba->ib_cur_slot &= ~mhba->regs->cl_slot_num_mask;
	mhba->ib_cur_slot |= (cur_ib_entry & mhba->regs->cl_slot_num_mask);
	if (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC) {
		*ib_entry = mhba->ib_list + cur_ib_entry *
				sizeof(struct mvumi_dyn_list_entry);
	} else {
		*ib_entry = mhba->ib_list + cur_ib_entry * mhba->ib_max_size;
	}
	atomic_inc(&mhba->fw_outstanding);
}
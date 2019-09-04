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
struct hfi1_filedata {int /*<<< orphan*/ * entry_to_rb; int /*<<< orphan*/ * invalid_tids; scalar_t__ handler; struct hfi1_ctxtdata* uctxt; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  tid_used_list; int /*<<< orphan*/  tid_full_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_TID_SET_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_mmu_rb_unregister (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_exp_tids (struct hfi1_ctxtdata*,int /*<<< orphan*/ *,struct hfi1_filedata*) ; 

void hfi1_user_exp_rcv_free(struct hfi1_filedata *fd)
{
	struct hfi1_ctxtdata *uctxt = fd->uctxt;

	/*
	 * The notifier would have been removed when the process'es mm
	 * was freed.
	 */
	if (fd->handler) {
		hfi1_mmu_rb_unregister(fd->handler);
	} else {
		if (!EXP_TID_SET_EMPTY(uctxt->tid_full_list))
			unlock_exp_tids(uctxt, &uctxt->tid_full_list, fd);
		if (!EXP_TID_SET_EMPTY(uctxt->tid_used_list))
			unlock_exp_tids(uctxt, &uctxt->tid_used_list, fd);
	}

	kfree(fd->invalid_tids);
	fd->invalid_tids = NULL;

	kfree(fd->entry_to_rb);
	fd->entry_to_rb = NULL;
}
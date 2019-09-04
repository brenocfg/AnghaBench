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
struct hfi1_ctxtdata {int /*<<< orphan*/ * groups; int /*<<< orphan*/  tid_used_list; int /*<<< orphan*/  tid_full_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_TID_SET_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hfi1_clear_tids (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_exp_tid_group_init (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void hfi1_free_ctxt_rcv_groups(struct hfi1_ctxtdata *rcd)
{
	WARN_ON(!EXP_TID_SET_EMPTY(rcd->tid_full_list));
	WARN_ON(!EXP_TID_SET_EMPTY(rcd->tid_used_list));

	kfree(rcd->groups);
	rcd->groups = NULL;
	hfi1_exp_tid_group_init(rcd);

	hfi1_clear_tids(rcd);
}
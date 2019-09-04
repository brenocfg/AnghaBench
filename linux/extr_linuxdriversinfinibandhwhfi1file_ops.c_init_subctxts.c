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
struct hfi1_user_info {int /*<<< orphan*/  subctxt_id; int /*<<< orphan*/  subctxt_cnt; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  event_flags; int /*<<< orphan*/  subctxt_id; int /*<<< orphan*/  subctxt_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_CTXT_BASE_UNINIT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_subctxts(struct hfi1_ctxtdata *uctxt,
			  const struct hfi1_user_info *uinfo)
{
	uctxt->subctxt_cnt = uinfo->subctxt_cnt;
	uctxt->subctxt_id = uinfo->subctxt_id;
	set_bit(HFI1_CTXT_BASE_UNINIT, &uctxt->event_flags);
}
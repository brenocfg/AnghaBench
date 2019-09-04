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
struct hfi1_ctxtdata {int /*<<< orphan*/  tid_full_list; int /*<<< orphan*/  tid_used_list; int /*<<< orphan*/  tid_group_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_exp_tid_set_init (int /*<<< orphan*/ *) ; 

void hfi1_exp_tid_group_init(struct hfi1_ctxtdata *rcd)
{
	hfi1_exp_tid_set_init(&rcd->tid_group_list);
	hfi1_exp_tid_set_init(&rcd->tid_used_list);
	hfi1_exp_tid_set_init(&rcd->tid_full_list);
}
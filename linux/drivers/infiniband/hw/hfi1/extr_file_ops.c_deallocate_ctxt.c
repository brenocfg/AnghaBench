#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hfi1_ctxtdata {TYPE_2__* dd; } ;
struct TYPE_4__ {scalar_t__ freectxts; scalar_t__ num_user_contexts; } ;
struct TYPE_3__ {int /*<<< orphan*/  sps_ctxts; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_enable_all (TYPE_2__*) ; 
 int /*<<< orphan*/  hfi1_free_ctxt (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_mutex ; 
 TYPE_1__ hfi1_stats ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deallocate_ctxt(struct hfi1_ctxtdata *uctxt)
{
	mutex_lock(&hfi1_mutex);
	hfi1_stats.sps_ctxts--;
	if (++uctxt->dd->freectxts == uctxt->dd->num_user_contexts)
		aspm_enable_all(uctxt->dd);
	mutex_unlock(&hfi1_mutex);

	hfi1_free_ctxt(uctxt);
}
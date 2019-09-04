#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rc_delayed_comp; int /*<<< orphan*/ * rc_qacks; int /*<<< orphan*/ * rc_acks; } ;
struct TYPE_5__ {TYPE_1__ rvp; } ;
struct hfi1_pportdata {TYPE_2__ ibport_data; int /*<<< orphan*/ * scntrs; int /*<<< orphan*/ * cntrs; } ;
struct TYPE_6__ {scalar_t__ function; } ;
struct hfi1_devdata {int num_pports; int /*<<< orphan*/ * update_cntr_wq; int /*<<< orphan*/ * cntrnames; int /*<<< orphan*/ * scntrs; int /*<<< orphan*/ * cntrs; int /*<<< orphan*/ * portcntrnames; TYPE_3__ synth_stats_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_cntrs(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd;
	int i;

	if (dd->synth_stats_timer.function)
		del_timer_sync(&dd->synth_stats_timer);
	ppd = (struct hfi1_pportdata *)(dd + 1);
	for (i = 0; i < dd->num_pports; i++, ppd++) {
		kfree(ppd->cntrs);
		kfree(ppd->scntrs);
		free_percpu(ppd->ibport_data.rvp.rc_acks);
		free_percpu(ppd->ibport_data.rvp.rc_qacks);
		free_percpu(ppd->ibport_data.rvp.rc_delayed_comp);
		ppd->cntrs = NULL;
		ppd->scntrs = NULL;
		ppd->ibport_data.rvp.rc_acks = NULL;
		ppd->ibport_data.rvp.rc_qacks = NULL;
		ppd->ibport_data.rvp.rc_delayed_comp = NULL;
	}
	kfree(dd->portcntrnames);
	dd->portcntrnames = NULL;
	kfree(dd->cntrs);
	dd->cntrs = NULL;
	kfree(dd->scntrs);
	dd->scntrs = NULL;
	kfree(dd->cntrnames);
	dd->cntrnames = NULL;
	if (dd->update_cntr_wq) {
		destroy_workqueue(dd->update_cntr_wq);
		dd->update_cntr_wq = NULL;
	}
}
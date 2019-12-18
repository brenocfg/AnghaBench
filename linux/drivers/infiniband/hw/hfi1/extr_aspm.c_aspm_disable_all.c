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
typedef  scalar_t__ u16 ;
struct hfi1_devdata {scalar_t__ first_dyn_alloc_ctxt; int /*<<< orphan*/  aspm_disabled_cnt; } ;
struct hfi1_ctxtdata {int aspm_intr_enable; int /*<<< orphan*/  aspm_lock; int /*<<< orphan*/  aspm_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_disable (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void aspm_disable_all(struct hfi1_devdata *dd)
{
	struct hfi1_ctxtdata *rcd;
	unsigned long flags;
	u16 i;

	for (i = 0; i < dd->first_dyn_alloc_ctxt; i++) {
		rcd = hfi1_rcd_get_by_index(dd, i);
		if (rcd) {
			del_timer_sync(&rcd->aspm_timer);
			spin_lock_irqsave(&rcd->aspm_lock, flags);
			rcd->aspm_intr_enable = false;
			spin_unlock_irqrestore(&rcd->aspm_lock, flags);
			hfi1_rcd_put(rcd);
		}
	}

	aspm_disable(dd);
	atomic_set(&dd->aspm_disabled_cnt, 0);
}
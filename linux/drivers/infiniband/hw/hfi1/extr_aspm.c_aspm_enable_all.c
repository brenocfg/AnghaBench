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
struct hfi1_devdata {scalar_t__ first_dyn_alloc_ctxt; } ;
struct hfi1_ctxtdata {int aspm_intr_enable; int aspm_enabled; int /*<<< orphan*/  aspm_lock; } ;

/* Variables and functions */
 scalar_t__ ASPM_MODE_DYNAMIC ; 
 int /*<<< orphan*/  aspm_enable (struct hfi1_devdata*) ; 
 scalar_t__ aspm_mode ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void aspm_enable_all(struct hfi1_devdata *dd)
{
	struct hfi1_ctxtdata *rcd;
	unsigned long flags;
	u16 i;

	aspm_enable(dd);

	if (aspm_mode != ASPM_MODE_DYNAMIC)
		return;

	for (i = 0; i < dd->first_dyn_alloc_ctxt; i++) {
		rcd = hfi1_rcd_get_by_index(dd, i);
		if (rcd) {
			spin_lock_irqsave(&rcd->aspm_lock, flags);
			rcd->aspm_intr_enable = true;
			rcd->aspm_enabled = true;
			spin_unlock_irqrestore(&rcd->aspm_lock, flags);
			hfi1_rcd_put(rcd);
		}
	}
}
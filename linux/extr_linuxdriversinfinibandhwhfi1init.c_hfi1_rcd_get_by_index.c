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
typedef  size_t u16 ;
struct hfi1_devdata {int /*<<< orphan*/  uctxt_lock; struct hfi1_ctxtdata** rcd; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_rcd_get (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct hfi1_ctxtdata *hfi1_rcd_get_by_index(struct hfi1_devdata *dd, u16 ctxt)
{
	unsigned long flags;
	struct hfi1_ctxtdata *rcd = NULL;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	if (dd->rcd[ctxt]) {
		rcd = dd->rcd[ctxt];
		if (!hfi1_rcd_get(rcd))
			rcd = NULL;
	}
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	return rcd;
}
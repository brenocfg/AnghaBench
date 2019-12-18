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
struct timer_list {int dummy; } ;
struct hfi1_ctxtdata {int aspm_enabled; int /*<<< orphan*/  aspm_lock; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_enable_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspm_timer ; 
 struct hfi1_ctxtdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hfi1_ctxtdata* rcd ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static  void aspm_ctx_timer_function(struct timer_list *t)
{
	struct hfi1_ctxtdata *rcd = from_timer(rcd, t, aspm_timer);
	unsigned long flags;

	spin_lock_irqsave(&rcd->aspm_lock, flags);
	aspm_enable_dec(rcd->dd);
	rcd->aspm_enabled = true;
	spin_unlock_irqrestore(&rcd->aspm_lock, flags);
}
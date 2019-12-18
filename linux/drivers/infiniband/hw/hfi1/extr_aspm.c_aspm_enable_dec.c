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
struct hfi1_devdata {int /*<<< orphan*/  aspm_lock; int /*<<< orphan*/  aspm_disabled_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_enable (struct hfi1_devdata*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static  void aspm_enable_dec(struct hfi1_devdata *dd)
{
	unsigned long flags;

	spin_lock_irqsave(&dd->aspm_lock, flags);
	if (atomic_dec_and_test(&dd->aspm_disabled_cnt))
		aspm_enable(dd);
	spin_unlock_irqrestore(&dd->aspm_lock, flags);
}
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
 int /*<<< orphan*/  aspm_disable (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static  void aspm_disable_inc(struct hfi1_devdata *dd)
{
	unsigned long flags;

	spin_lock_irqsave(&dd->aspm_lock, flags);
	aspm_disable(dd);
	atomic_inc(&dd->aspm_disabled_cnt);
	spin_unlock_irqrestore(&dd->aspm_lock, flags);
}
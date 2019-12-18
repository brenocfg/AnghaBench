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
typedef  int /*<<< orphan*/  u32 ;
struct budget {int /*<<< orphan*/  debilock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int ttpci_budget_debiwrite_nolock (struct budget*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

int ttpci_budget_debiwrite(struct budget *budget, u32 config, int addr,
			   int count, u32 value, int uselocks, int nobusyloop)
{
	if (count > 4 || count <= 0)
		return 0;

	if (uselocks) {
		unsigned long flags;
		int result;

		spin_lock_irqsave(&budget->debilock, flags);
		result = ttpci_budget_debiwrite_nolock(budget, config, addr,
						count, value, nobusyloop);
		spin_unlock_irqrestore(&budget->debilock, flags);
		return result;
	}
	return ttpci_budget_debiwrite_nolock(budget, config, addr,
					     count, value, nobusyloop);
}
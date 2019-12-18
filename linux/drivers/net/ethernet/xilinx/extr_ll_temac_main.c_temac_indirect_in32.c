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
typedef  int u32 ;
struct temac_local {int /*<<< orphan*/  indirect_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int temac_indirect_in32_locked (struct temac_local*,int) ; 

u32 temac_indirect_in32(struct temac_local *lp, int reg)
{
	unsigned long flags;
	int val;

	spin_lock_irqsave(lp->indirect_lock, flags);
	val = temac_indirect_in32_locked(lp, reg);
	spin_unlock_irqrestore(lp->indirect_lock, flags);
	return val;
}
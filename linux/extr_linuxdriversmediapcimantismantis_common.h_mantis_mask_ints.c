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
struct mantis_pci {int /*<<< orphan*/  intmask_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_INT_MASK ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void mantis_mask_ints(struct mantis_pci *mantis, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&mantis->intmask_lock, flags);
	mmwrite(mmread(MANTIS_INT_MASK) & ~mask, MANTIS_INT_MASK);
	spin_unlock_irqrestore(&mantis->intmask_lock, flags);
}
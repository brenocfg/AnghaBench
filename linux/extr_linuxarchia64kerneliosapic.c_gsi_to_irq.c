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

/* Variables and functions */
 int __gsi_to_irq (unsigned int) ; 
 int /*<<< orphan*/  iosapic_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
gsi_to_irq (unsigned int gsi)
{
	unsigned long flags;
	int irq;

	spin_lock_irqsave(&iosapic_lock, flags);
	irq = __gsi_to_irq(gsi);
	spin_unlock_irqrestore(&iosapic_lock, flags);
	return irq;
}
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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  reserve_irq_vector_locked (struct irq_data*) ; 
 int /*<<< orphan*/  vector_lock ; 

__attribute__((used)) static int reserve_irq_vector(struct irq_data *irqd)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&vector_lock, flags);
	reserve_irq_vector_locked(irqd);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	return 0;
}
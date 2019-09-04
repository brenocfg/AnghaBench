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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int assign_vector_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vector_lock ; 
 int /*<<< orphan*/  vector_searchmask ; 

__attribute__((used)) static int assign_irq_vector(struct irq_data *irqd, const struct cpumask *dest)
{
	unsigned long flags;
	int ret;

	raw_spin_lock_irqsave(&vector_lock, flags);
	cpumask_and(vector_searchmask, dest, cpu_online_mask);
	ret = assign_vector_locked(irqd, vector_searchmask);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	return ret;
}
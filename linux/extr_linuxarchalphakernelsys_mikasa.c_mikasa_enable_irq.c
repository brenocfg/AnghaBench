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
struct irq_data {int irq; } ;

/* Variables and functions */
 int cached_irq_mask ; 
 int /*<<< orphan*/  mikasa_update_irq_hw (int) ; 

__attribute__((used)) static inline void
mikasa_enable_irq(struct irq_data *d)
{
	mikasa_update_irq_hw(cached_irq_mask |= 1 << (d->irq - 16));
}
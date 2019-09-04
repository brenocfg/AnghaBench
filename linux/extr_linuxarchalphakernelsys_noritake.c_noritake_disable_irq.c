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
 int /*<<< orphan*/  noritake_update_irq_hw (int,int) ; 

__attribute__((used)) static void
noritake_disable_irq(struct irq_data *d)
{
	noritake_update_irq_hw(d->irq, cached_irq_mask &= ~(1 << (d->irq - 16)));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {unsigned int irq; } ;
struct TYPE_2__ {int imask; } ;

/* Variables and functions */
 unsigned int CRIME_IRQ_BASE ; 
 TYPE_1__* crime ; 
 int crime_mask ; 

__attribute__((used)) static void enable_mace_irq(struct irq_data *d)
{
	unsigned int bit = d->irq - CRIME_IRQ_BASE;

	crime_mask |= (1 << bit);
	crime->imask = crime_mask;
}
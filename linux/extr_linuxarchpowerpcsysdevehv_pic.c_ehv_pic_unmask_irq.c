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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ev_int_set_mask (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int virq_to_hw (int /*<<< orphan*/ ) ; 

void ehv_pic_unmask_irq(struct irq_data *d)
{
	unsigned int src = virq_to_hw(d->irq);

	ev_int_set_mask(src, 0);
}
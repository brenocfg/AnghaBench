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
struct intc_desc_int {int dummy; } ;
typedef  int /*<<< orphan*/  intc_enum ;
struct TYPE_2__ {struct intc_desc_int* desc; int /*<<< orphan*/  enum_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  intc_big_lock ; 
 TYPE_1__* intc_irq_xlate ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intc_irq_xlate_set(unsigned int irq, intc_enum id, struct intc_desc_int *d)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&intc_big_lock, flags);
	intc_irq_xlate[irq].enum_id = id;
	intc_irq_xlate[irq].desc = d;
	raw_spin_unlock_irqrestore(&intc_big_lock, flags);
}
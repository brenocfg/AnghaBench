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
typedef  int u32 ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct ipic {int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int bit; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 struct ipic* ipic_from_irq (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipic_info ; 
 int /*<<< orphan*/  ipic_lock ; 
 int ipic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipic_unmask_irq(struct irq_data *d)
{
	struct ipic *ipic = ipic_from_irq(d->irq);
	unsigned int src = irqd_to_hwirq(d);
	unsigned long flags;
	u32 temp;

	raw_spin_lock_irqsave(&ipic_lock, flags);

	temp = ipic_read(ipic->regs, ipic_info[src].mask);
	temp |= (1 << (31 - ipic_info[src].bit));
	ipic_write(ipic->regs, ipic_info[src].mask, temp);

	raw_spin_unlock_irqrestore(&ipic_lock, flags);
}
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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int CLEAR_INTR (int,int) ; 
 int ENABLE_INTR (int,int) ; 
 int /*<<< orphan*/  IRQ_ENABLE_BANK ; 
 int /*<<< orphan*/  pdc_lock ; 
 int pdc_reg_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdc_reg_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdc_enable_intr(struct irq_data *d, bool on)
{
	int pin_out = d->hwirq;
	u32 index, mask;
	u32 enable;

	index = pin_out / 32;
	mask = pin_out % 32;

	raw_spin_lock(&pdc_lock);
	enable = pdc_reg_read(IRQ_ENABLE_BANK, index);
	enable = on ? ENABLE_INTR(enable, mask) : CLEAR_INTR(enable, mask);
	pdc_reg_write(IRQ_ENABLE_BANK, index, enable);
	raw_spin_unlock(&pdc_lock);
}
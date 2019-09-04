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
typedef  int /*<<< orphan*/  u8 ;
struct lp8788_irq_data {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  lp; int /*<<< orphan*/ * enabled; } ;
struct irq_data {int hwirq; } ;
typedef  enum lp8788_int_id { ____Placeholder_lp8788_int_id } lp8788_int_id ;

/* Variables and functions */
 int /*<<< orphan*/  _irq_to_enable_addr (int) ; 
 int /*<<< orphan*/  _irq_to_mask (int) ; 
 int /*<<< orphan*/  _irq_to_val (int,int /*<<< orphan*/ ) ; 
 struct lp8788_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lp8788_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lp8788_irq_bus_sync_unlock(struct irq_data *data)
{
	struct lp8788_irq_data *irqd = irq_data_get_irq_chip_data(data);
	enum lp8788_int_id irq = data->hwirq;
	u8 addr, mask, val;

	addr = _irq_to_enable_addr(irq);
	mask = _irq_to_mask(irq);
	val = _irq_to_val(irq, irqd->enabled[irq]);

	lp8788_update_bits(irqd->lp, addr, mask, val);

	mutex_unlock(&irqd->irq_lock);
}
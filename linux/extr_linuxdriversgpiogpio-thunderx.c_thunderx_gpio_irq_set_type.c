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
typedef  int u64 ;
struct thunderx_line {int fil_bits; int /*<<< orphan*/  line; struct thunderx_gpio* txgpio; } ;
struct thunderx_gpio {int /*<<< orphan*/  lock; scalar_t__ register_base; int /*<<< orphan*/  od_mask; int /*<<< orphan*/  invert_mask; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int GPIO_BIT_CFG_INT_EN ; 
 int GPIO_BIT_CFG_INT_TYPE ; 
 int GPIO_BIT_CFG_PIN_XOR ; 
 int IRQ_SET_MASK_OK ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 scalar_t__ bit_cfg_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_fasteoi_ack_irq ; 
 int /*<<< orphan*/  handle_fasteoi_mask_irq ; 
 struct thunderx_line* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static int thunderx_gpio_irq_set_type(struct irq_data *data,
				      unsigned int flow_type)
{
	struct thunderx_line *txline = irq_data_get_irq_chip_data(data);
	struct thunderx_gpio *txgpio = txline->txgpio;
	u64 bit_cfg;

	irqd_set_trigger_type(data, flow_type);

	bit_cfg = txline->fil_bits | GPIO_BIT_CFG_INT_EN;

	if (flow_type & IRQ_TYPE_EDGE_BOTH) {
		irq_set_handler_locked(data, handle_fasteoi_ack_irq);
		bit_cfg |= GPIO_BIT_CFG_INT_TYPE;
	} else {
		irq_set_handler_locked(data, handle_fasteoi_mask_irq);
	}

	raw_spin_lock(&txgpio->lock);
	if (flow_type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_LEVEL_LOW)) {
		bit_cfg |= GPIO_BIT_CFG_PIN_XOR;
		set_bit(txline->line, txgpio->invert_mask);
	} else {
		clear_bit(txline->line, txgpio->invert_mask);
	}
	clear_bit(txline->line, txgpio->od_mask);
	writeq(bit_cfg, txgpio->register_base + bit_cfg_reg(txline->line));
	raw_spin_unlock(&txgpio->lock);

	return IRQ_SET_MASK_OK;
}
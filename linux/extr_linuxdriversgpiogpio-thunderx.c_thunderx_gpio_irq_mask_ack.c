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
struct thunderx_line {int /*<<< orphan*/  line; TYPE_1__* txgpio; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ register_base; } ;

/* Variables and functions */
 int GPIO_INTR_ENA_W1C ; 
 int GPIO_INTR_INTR ; 
 scalar_t__ intr_reg (int /*<<< orphan*/ ) ; 
 struct thunderx_line* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void thunderx_gpio_irq_mask_ack(struct irq_data *data)
{
	struct thunderx_line *txline = irq_data_get_irq_chip_data(data);

	writeq(GPIO_INTR_ENA_W1C | GPIO_INTR_INTR,
	       txline->txgpio->register_base + intr_reg(txline->line));
}
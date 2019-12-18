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
struct pic32_gpio_bank {scalar_t__ reg_base; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CNCON_REG ; 
 int /*<<< orphan*/  PIC32_CNCON_ON ; 
 scalar_t__ PIC32_SET (int /*<<< orphan*/ ) ; 
 struct pic32_gpio_bank* irqd_to_bank (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pic32_gpio_irq_unmask(struct irq_data *data)
{
	struct pic32_gpio_bank *bank = irqd_to_bank(data);

	writel(BIT(PIC32_CNCON_ON), bank->reg_base + PIC32_SET(CNCON_REG));
}
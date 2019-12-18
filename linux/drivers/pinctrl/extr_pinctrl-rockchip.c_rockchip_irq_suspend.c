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
struct rockchip_pin_bank {int /*<<< orphan*/  clk; int /*<<< orphan*/  saved_masks; } ;
struct irq_data {int dummy; } ;
struct irq_chip_generic {int /*<<< orphan*/  wake_active; struct rockchip_pin_bank* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_INTMASK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_reg_readl (struct irq_chip_generic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_irq_suspend(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct rockchip_pin_bank *bank = gc->private;

	clk_enable(bank->clk);
	bank->saved_masks = irq_reg_readl(gc, GPIO_INTMASK);
	irq_reg_writel(gc, ~gc->wake_active, GPIO_INTMASK);
	clk_disable(bank->clk);
}
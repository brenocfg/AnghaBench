#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int debounce_en; int debounce; } ;
struct gpio_bank {int dbck_enable_mask; int dbck_enabled; int /*<<< orphan*/  dbck; TYPE_2__* regs; scalar_t__ base; TYPE_1__ context; int /*<<< orphan*/  dbck_flag; } ;
struct TYPE_4__ {scalar_t__ debounce; scalar_t__ debounce_en; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void omap_clear_gpio_debounce(struct gpio_bank *bank, unsigned offset)
{
	u32 gpio_bit = BIT(offset);

	if (!bank->dbck_flag)
		return;

	if (!(bank->dbck_enable_mask & gpio_bit))
		return;

	bank->dbck_enable_mask &= ~gpio_bit;
	bank->context.debounce_en &= ~gpio_bit;
        writel_relaxed(bank->context.debounce_en,
		     bank->base + bank->regs->debounce_en);

	if (!bank->dbck_enable_mask) {
		bank->context.debounce = 0;
		writel_relaxed(bank->context.debounce, bank->base +
			     bank->regs->debounce);
		clk_disable(bank->dbck);
		bank->dbck_enabled = false;
	}
}
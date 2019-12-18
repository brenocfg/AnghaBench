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
struct gpio_bank {int dbck_enabled; int /*<<< orphan*/  dbck; TYPE_1__* regs; scalar_t__ base; scalar_t__ dbck_enable_mask; } ;
struct TYPE_2__ {scalar_t__ debounce_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void omap_gpio_dbck_disable(struct gpio_bank *bank)
{
	if (bank->dbck_enable_mask && bank->dbck_enabled) {
		/*
		 * Disable debounce before cutting it's clock. If debounce is
		 * enabled but the clock is not, GPIO module seems to be unable
		 * to detect events and generate interrupts at least on OMAP3.
		 */
		writel_relaxed(0, bank->base + bank->regs->debounce_en);

		clk_disable(bank->dbck);
		bank->dbck_enabled = false;
	}
}
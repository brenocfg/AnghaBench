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
typedef  void* u32 ;
struct TYPE_4__ {unsigned int debounce; void* debounce_en; } ;
struct gpio_bank {TYPE_2__ context; void* dbck_enable_mask; int /*<<< orphan*/  dbck; TYPE_1__* regs; scalar_t__ base; int /*<<< orphan*/  dbck_flag; } ;
struct TYPE_3__ {scalar_t__ debounce_en; scalar_t__ debounce; } ;

/* Variables and functions */
 void* BIT (unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 unsigned int OMAP4_GPIO_DEBOUNCINGTIME_MASK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_gpio_dbck_enable (struct gpio_bank*) ; 
 void* omap_gpio_rmw (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int omap2_set_gpio_debounce(struct gpio_bank *bank, unsigned offset,
				   unsigned debounce)
{
	u32			val;
	u32			l;
	bool			enable = !!debounce;

	if (!bank->dbck_flag)
		return -ENOTSUPP;

	if (enable) {
		debounce = DIV_ROUND_UP(debounce, 31) - 1;
		if ((debounce & OMAP4_GPIO_DEBOUNCINGTIME_MASK) != debounce)
			return -EINVAL;
	}

	l = BIT(offset);

	clk_enable(bank->dbck);
	writel_relaxed(debounce, bank->base + bank->regs->debounce);

	val = omap_gpio_rmw(bank->base + bank->regs->debounce_en, l, enable);
	bank->dbck_enable_mask = val;

	clk_disable(bank->dbck);
	/*
	 * Enable debounce clock per module.
	 * This call is mandatory because in omap_gpio_request() when
	 * *_runtime_get_sync() is called,  _gpio_dbck_enable() within
	 * runtime callbck fails to turn on dbck because dbck_enable_mask
	 * used within _gpio_dbck_enable() is still not initialized at
	 * that point. Therefore we have to enable dbck here.
	 */
	omap_gpio_dbck_enable(bank);
	if (bank->dbck_enable_mask) {
		bank->context.debounce = debounce;
		bank->context.debounce_en = val;
	}

	return 0;
}
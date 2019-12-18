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
struct st_gpio_bank {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ REG_PIO_CLR_POUT ; 
 scalar_t__ REG_PIO_SET_POUT ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void __st_gpio_set(struct st_gpio_bank *bank,
	unsigned offset, int value)
{
	if (value)
		writel(BIT(offset), bank->base + REG_PIO_SET_POUT);
	else
		writel(BIT(offset), bank->base + REG_PIO_CLR_POUT);
}
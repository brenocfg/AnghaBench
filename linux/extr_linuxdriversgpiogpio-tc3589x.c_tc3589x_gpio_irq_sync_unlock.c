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
typedef  scalar_t__ u8 ;
struct tc3589x_gpio {scalar_t__** oldregs; scalar_t__** regs; int /*<<< orphan*/  irq_lock; struct tc3589x* tc3589x; } ;
struct tc3589x {int dummy; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int CACHE_NR_BANKS ; 
 int CACHE_NR_REGS ; 
#define  REG_IBE 135 
#define  REG_IE 134 
#define  REG_IEV 133 
#define  REG_IS 132 
#define  TC3589x_GPIOIBE0 131 
#define  TC3589x_GPIOIE0 130 
#define  TC3589x_GPIOIEV0 129 
#define  TC3589x_GPIOIS0 128 
 struct tc3589x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc3589x_reg_write (struct tc3589x*,scalar_t__ const,scalar_t__) ; 

__attribute__((used)) static void tc3589x_gpio_irq_sync_unlock(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	struct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	static const u8 regmap[] = {
		[REG_IBE]	= TC3589x_GPIOIBE0,
		[REG_IEV]	= TC3589x_GPIOIEV0,
		[REG_IS]	= TC3589x_GPIOIS0,
		[REG_IE]	= TC3589x_GPIOIE0,
	};
	int i, j;

	for (i = 0; i < CACHE_NR_REGS; i++) {
		for (j = 0; j < CACHE_NR_BANKS; j++) {
			u8 old = tc3589x_gpio->oldregs[i][j];
			u8 new = tc3589x_gpio->regs[i][j];

			if (new == old)
				continue;

			tc3589x_gpio->oldregs[i][j] = new;
			tc3589x_reg_write(tc3589x, regmap[i] + j * 8, new);
		}
	}

	mutex_unlock(&tc3589x_gpio->irq_lock);
}
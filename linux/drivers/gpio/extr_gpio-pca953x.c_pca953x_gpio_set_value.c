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
typedef  int /*<<< orphan*/  u8 ;
struct pca953x_chip {int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  regmap; TYPE_1__* regs; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 unsigned int BANK_SZ ; 
 int /*<<< orphan*/  BIT (unsigned int) ; 
 struct pca953x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pca953x_recalc_addr (struct pca953x_chip*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pca953x_gpio_set_value(struct gpio_chip *gc, unsigned off, int val)
{
	struct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 outreg = pca953x_recalc_addr(chip, chip->regs->output, off,
					true, false);
	u8 bit = BIT(off % BANK_SZ);

	mutex_lock(&chip->i2c_lock);
	regmap_write_bits(chip->regmap, outreg, bit, val ? bit : 0);
	mutex_unlock(&chip->i2c_lock);
}
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
typedef  void* u8 ;
struct pca953x_chip {unsigned int* reg_output; unsigned int* reg_direction; int /*<<< orphan*/  i2c_lock; TYPE_1__* regs; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 unsigned int BANK_SZ ; 
 struct pca953x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pca953x_write_single (struct pca953x_chip*,int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static int pca953x_gpio_direction_output(struct gpio_chip *gc,
		unsigned off, int val)
{
	struct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 reg_val;
	int ret;

	mutex_lock(&chip->i2c_lock);
	/* set output level */
	if (val)
		reg_val = chip->reg_output[off / BANK_SZ]
			| (1u << (off % BANK_SZ));
	else
		reg_val = chip->reg_output[off / BANK_SZ]
			& ~(1u << (off % BANK_SZ));

	ret = pca953x_write_single(chip, chip->regs->output, reg_val, off);
	if (ret)
		goto exit;

	chip->reg_output[off / BANK_SZ] = reg_val;

	/* then direction */
	reg_val = chip->reg_direction[off / BANK_SZ] & ~(1u << (off % BANK_SZ));
	ret = pca953x_write_single(chip, chip->regs->direction, reg_val, off);
	if (ret)
		goto exit;

	chip->reg_direction[off / BANK_SZ] = reg_val;
exit:
	mutex_unlock(&chip->i2c_lock);
	return ret;
}
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
typedef  unsigned int u8 ;
struct pca953x_chip {int /*<<< orphan*/  i2c_lock; TYPE_1__* regs; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int MAX_BANK ; 
 int NBANK (struct pca953x_chip*) ; 
 struct pca953x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pca953x_read_regs (struct pca953x_chip*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pca953x_write_regs (struct pca953x_chip*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void pca953x_gpio_set_multiple(struct gpio_chip *gc,
				      unsigned long *mask, unsigned long *bits)
{
	struct pca953x_chip *chip = gpiochip_get_data(gc);
	unsigned int bank_mask, bank_val;
	int bank;
	u8 reg_val[MAX_BANK];
	int ret;

	mutex_lock(&chip->i2c_lock);
	ret = pca953x_read_regs(chip, chip->regs->output, reg_val);
	if (ret)
		goto exit;

	for (bank = 0; bank < NBANK(chip); bank++) {
		bank_mask = mask[bank / sizeof(*mask)] >>
			   ((bank % sizeof(*mask)) * 8);
		if (bank_mask) {
			bank_val = bits[bank / sizeof(*bits)] >>
				  ((bank % sizeof(*bits)) * 8);
			bank_val &= bank_mask;
			reg_val[bank] = (reg_val[bank] & ~bank_mask) | bank_val;
		}
	}

	pca953x_write_regs(chip, chip->regs->output, reg_val);
exit:
	mutex_unlock(&chip->i2c_lock);
}
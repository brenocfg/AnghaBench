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
typedef  unsigned int u8 ;
struct TYPE_3__ {int ngpio; } ;
struct pca953x_chip {unsigned int* reg_output; int /*<<< orphan*/  i2c_lock; TYPE_2__* regs; int /*<<< orphan*/  client; TYPE_1__ gpio_chip; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {int output; } ;

/* Variables and functions */
 int BANK_SZ ; 
 int MAX_BANK ; 
 int NBANK (struct pca953x_chip*) ; 
 int fls (int) ; 
 struct pca953x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int i2c_smbus_write_i2c_block_data (int /*<<< orphan*/ ,int,int,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pca953x_gpio_set_multiple(struct gpio_chip *gc,
				      unsigned long *mask, unsigned long *bits)
{
	struct pca953x_chip *chip = gpiochip_get_data(gc);
	unsigned int bank_mask, bank_val;
	int bank_shift, bank;
	u8 reg_val[MAX_BANK];
	int ret;

	bank_shift = fls((chip->gpio_chip.ngpio - 1) / BANK_SZ);

	mutex_lock(&chip->i2c_lock);
	memcpy(reg_val, chip->reg_output, NBANK(chip));
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

	ret = i2c_smbus_write_i2c_block_data(chip->client,
					     chip->regs->output << bank_shift,
					     NBANK(chip), reg_val);
	if (ret)
		goto exit;

	memcpy(chip->reg_output, reg_val, NBANK(chip));
exit:
	mutex_unlock(&chip->i2c_lock);
}
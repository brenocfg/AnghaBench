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
typedef  int /*<<< orphan*/  u8 ;
struct pca953x_chip {int driver_data; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BANK_SZ ; 
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  PCAL953X_PULL_EN ; 
 int /*<<< orphan*/  PCAL953X_PULL_SEL ; 
 int PCA_PCAL ; 
 unsigned long PIN_CONFIG_BIAS_PULL_DOWN ; 
 unsigned long PIN_CONFIG_BIAS_PULL_UP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pca953x_recalc_addr (struct pca953x_chip*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca953x_gpio_set_pull_up_down(struct pca953x_chip *chip,
					 unsigned int offset,
					 unsigned long config)
{
	u8 pull_en_reg = pca953x_recalc_addr(chip, PCAL953X_PULL_EN, offset,
					     true, false);
	u8 pull_sel_reg = pca953x_recalc_addr(chip, PCAL953X_PULL_SEL, offset,
					      true, false);
	u8 bit = BIT(offset % BANK_SZ);
	int ret;

	/*
	 * pull-up/pull-down configuration requires PCAL extended
	 * registers
	 */
	if (!(chip->driver_data & PCA_PCAL))
		return -ENOTSUPP;

	mutex_lock(&chip->i2c_lock);

	/* Disable pull-up/pull-down */
	ret = regmap_write_bits(chip->regmap, pull_en_reg, bit, 0);
	if (ret)
		goto exit;

	/* Configure pull-up/pull-down */
	if (config == PIN_CONFIG_BIAS_PULL_UP)
		ret = regmap_write_bits(chip->regmap, pull_sel_reg, bit, bit);
	else if (config == PIN_CONFIG_BIAS_PULL_DOWN)
		ret = regmap_write_bits(chip->regmap, pull_sel_reg, bit, 0);
	if (ret)
		goto exit;

	/* Enable pull-up/pull-down */
	ret = regmap_write_bits(chip->regmap, pull_en_reg, bit, bit);

exit:
	mutex_unlock(&chip->i2c_lock);
	return ret;
}
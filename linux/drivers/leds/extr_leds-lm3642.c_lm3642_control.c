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
typedef  int u8 ;
struct lm3642_chip_data {int /*<<< orphan*/  regmap; scalar_t__ tx_pin; int /*<<< orphan*/  dev; int /*<<< orphan*/  strobe_pin; int /*<<< orphan*/  torch_pin; scalar_t__ last_flag; } ;
typedef  enum lm3642_mode { ____Placeholder_lm3642_mode } lm3642_mode ;

/* Variables and functions */
 int FLASH_I_MASK ; 
 int FLASH_I_SHIFT ; 
#define  MODES_FLASH 131 
#define  MODES_INDIC 130 
#define  MODES_STASNDBY 129 
#define  MODES_TORCH 128 
 int MODE_BITS_MASK ; 
 int MODE_BITS_SHIFT ; 
 int /*<<< orphan*/  REG_ENABLE ; 
 int /*<<< orphan*/  REG_FLAG ; 
 int /*<<< orphan*/  REG_I_CTRL ; 
 int STROBE_PIN_EN_MASK ; 
 int STROBE_PIN_EN_SHIFT ; 
 int TORCH_I_MASK ; 
 int TORCH_I_SHIFT ; 
 int TORCH_PIN_EN_MASK ; 
 int TORCH_PIN_EN_SHIFT ; 
 int TX_PIN_EN_MASK ; 
 int TX_PIN_EN_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm3642_control(struct lm3642_chip_data *chip,
			  u8 brightness, enum lm3642_mode opmode)
{
	int ret;

	ret = regmap_read(chip->regmap, REG_FLAG, &chip->last_flag);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read REG_FLAG Register\n");
		goto out;
	}

	if (chip->last_flag)
		dev_info(chip->dev, "Last FLAG is 0x%x\n", chip->last_flag);

	/* brightness 0 means off-state */
	if (!brightness)
		opmode = MODES_STASNDBY;

	switch (opmode) {
	case MODES_TORCH:
		ret = regmap_update_bits(chip->regmap, REG_I_CTRL,
					 TORCH_I_MASK << TORCH_I_SHIFT,
					 (brightness - 1) << TORCH_I_SHIFT);

		if (chip->torch_pin)
			opmode |= (TORCH_PIN_EN_MASK << TORCH_PIN_EN_SHIFT);
		break;

	case MODES_FLASH:
		ret = regmap_update_bits(chip->regmap, REG_I_CTRL,
					 FLASH_I_MASK << FLASH_I_SHIFT,
					 (brightness - 1) << FLASH_I_SHIFT);

		if (chip->strobe_pin)
			opmode |= (STROBE_PIN_EN_MASK << STROBE_PIN_EN_SHIFT);
		break;

	case MODES_INDIC:
		ret = regmap_update_bits(chip->regmap, REG_I_CTRL,
					 TORCH_I_MASK << TORCH_I_SHIFT,
					 (brightness - 1) << TORCH_I_SHIFT);
		break;

	case MODES_STASNDBY:

		break;

	default:
		return ret;
	}
	if (ret < 0) {
		dev_err(chip->dev, "Failed to write REG_I_CTRL Register\n");
		goto out;
	}

	if (chip->tx_pin)
		opmode |= (TX_PIN_EN_MASK << TX_PIN_EN_SHIFT);

	ret = regmap_update_bits(chip->regmap, REG_ENABLE,
				 MODE_BITS_MASK << MODE_BITS_SHIFT,
				 opmode << MODE_BITS_SHIFT);
out:
	return ret;
}
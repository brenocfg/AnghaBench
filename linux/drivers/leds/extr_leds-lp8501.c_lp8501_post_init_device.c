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
struct lp55xx_chip {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ clock_mode; int /*<<< orphan*/  pwr_sel; } ;

/* Variables and functions */
 scalar_t__ LP55XX_CLOCK_EXT ; 
 int /*<<< orphan*/  LP8501_DEFAULT_CFG ; 
 int /*<<< orphan*/  LP8501_ENABLE ; 
 int /*<<< orphan*/  LP8501_INT_CLK ; 
 int /*<<< orphan*/  LP8501_PWR_CONFIG_M ; 
 int /*<<< orphan*/  LP8501_REG_CONFIG ; 
 int /*<<< orphan*/  LP8501_REG_ENABLE ; 
 int /*<<< orphan*/  LP8501_REG_PWR_CONFIG ; 
 int lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lp8501_post_init_device(struct lp55xx_chip *chip)
{
	int ret;
	u8 val = LP8501_DEFAULT_CFG;

	ret = lp55xx_write(chip, LP8501_REG_ENABLE, LP8501_ENABLE);
	if (ret)
		return ret;

	/* Chip startup time is 500 us, 1 - 2 ms gives some margin */
	usleep_range(1000, 2000);

	if (chip->pdata->clock_mode != LP55XX_CLOCK_EXT)
		val |= LP8501_INT_CLK;

	ret = lp55xx_write(chip, LP8501_REG_CONFIG, val);
	if (ret)
		return ret;

	/* Power selection for each output */
	return lp55xx_update_bits(chip, LP8501_REG_PWR_CONFIG,
				LP8501_PWR_CONFIG_M, chip->pdata->pwr_sel);
}
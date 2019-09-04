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
struct lp55xx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP5562_CLK_INT ; 
 int /*<<< orphan*/  LP5562_CMD_DIRECT ; 
 int /*<<< orphan*/  LP5562_DEFAULT_CFG ; 
 int /*<<< orphan*/  LP5562_ENG_SEL_PWM ; 
 int /*<<< orphan*/  LP5562_REG_B_PWM ; 
 int /*<<< orphan*/  LP5562_REG_CONFIG ; 
 int /*<<< orphan*/  LP5562_REG_ENG_SEL ; 
 int /*<<< orphan*/  LP5562_REG_G_PWM ; 
 int /*<<< orphan*/  LP5562_REG_OP_MODE ; 
 int /*<<< orphan*/  LP5562_REG_R_PWM ; 
 int /*<<< orphan*/  LP5562_REG_W_PWM ; 
 int /*<<< orphan*/  lp5562_wait_opmode_done () ; 
 int /*<<< orphan*/  lp55xx_is_extclk_used (struct lp55xx_chip*) ; 
 int lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp5562_post_init_device(struct lp55xx_chip *chip)
{
	int ret;
	u8 cfg = LP5562_DEFAULT_CFG;

	/* Set all PWMs to direct control mode */
	ret = lp55xx_write(chip, LP5562_REG_OP_MODE, LP5562_CMD_DIRECT);
	if (ret)
		return ret;

	lp5562_wait_opmode_done();

	/* Update configuration for the clock setting */
	if (!lp55xx_is_extclk_used(chip))
		cfg |= LP5562_CLK_INT;

	ret = lp55xx_write(chip, LP5562_REG_CONFIG, cfg);
	if (ret)
		return ret;

	/* Initialize all channels PWM to zero -> leds off */
	lp55xx_write(chip, LP5562_REG_R_PWM, 0);
	lp55xx_write(chip, LP5562_REG_G_PWM, 0);
	lp55xx_write(chip, LP5562_REG_B_PWM, 0);
	lp55xx_write(chip, LP5562_REG_W_PWM, 0);

	/* Set LED map as register PWM by default */
	lp55xx_write(chip, LP5562_REG_ENG_SEL, LP5562_ENG_SEL_PWM);

	return 0;
}
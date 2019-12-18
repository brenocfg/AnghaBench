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
struct lp55xx_chip {int dummy; } ;

/* Variables and functions */
 int LP5523_AUTO_CLK ; 
 int LP5523_AUTO_INC ; 
 int LP5523_CP_AUTO ; 
 int LP5523_ENABLE ; 
 int LP5523_PWM_PWR_SAVE ; 
 int LP5523_PWR_SAVE ; 
 int /*<<< orphan*/  LP5523_REG_CONFIG ; 
 int /*<<< orphan*/  LP5523_REG_ENABLE ; 
 int /*<<< orphan*/  LP5523_REG_ENABLE_LEDS_LSB ; 
 int /*<<< orphan*/  LP5523_REG_ENABLE_LEDS_MSB ; 
 int lp5523_init_program_engine (struct lp55xx_chip*) ; 
 int lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lp5523_post_init_device(struct lp55xx_chip *chip)
{
	int ret;

	ret = lp55xx_write(chip, LP5523_REG_ENABLE, LP5523_ENABLE);
	if (ret)
		return ret;

	/* Chip startup time is 500 us, 1 - 2 ms gives some margin */
	usleep_range(1000, 2000);

	ret = lp55xx_write(chip, LP5523_REG_CONFIG,
			    LP5523_AUTO_INC | LP5523_PWR_SAVE |
			    LP5523_CP_AUTO | LP5523_AUTO_CLK |
			    LP5523_PWM_PWR_SAVE);
	if (ret)
		return ret;

	/* turn on all leds */
	ret = lp55xx_write(chip, LP5523_REG_ENABLE_LEDS_MSB, 0x01);
	if (ret)
		return ret;

	ret = lp55xx_write(chip, LP5523_REG_ENABLE_LEDS_LSB, 0xff);
	if (ret)
		return ret;

	return lp5523_init_program_engine(chip);
}
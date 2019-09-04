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
struct lm3560_flash {int /*<<< orphan*/  regmap; int /*<<< orphan*/  led_mode; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  peak; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_FLAG ; 
 int /*<<< orphan*/  REG_FLASH_TOUT ; 
 int /*<<< orphan*/  V4L2_FLASH_LED_MODE_NONE ; 
 int lm3560_mode_ctrl (struct lm3560_flash*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3560_init_device(struct lm3560_flash *flash)
{
	int rval;
	unsigned int reg_val;

	/* set peak current */
	rval = regmap_update_bits(flash->regmap,
				  REG_FLASH_TOUT, 0x60, flash->pdata->peak);
	if (rval < 0)
		return rval;
	/* output disable */
	flash->led_mode = V4L2_FLASH_LED_MODE_NONE;
	rval = lm3560_mode_ctrl(flash);
	if (rval < 0)
		return rval;
	/* reset faults */
	rval = regmap_read(flash->regmap, REG_FLAG, &reg_val);
	return rval;
}
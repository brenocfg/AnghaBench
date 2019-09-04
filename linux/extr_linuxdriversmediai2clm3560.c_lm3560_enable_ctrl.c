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
struct lm3560_flash {int /*<<< orphan*/  regmap; } ;
typedef  enum lm3560_led_id { ____Placeholder_lm3560_led_id } lm3560_led_id ;

/* Variables and functions */
 int LM3560_LED0 ; 
 int /*<<< orphan*/  REG_ENABLE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm3560_enable_ctrl(struct lm3560_flash *flash,
			      enum lm3560_led_id led_no, bool on)
{
	int rval;

	if (led_no == LM3560_LED0) {
		if (on)
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x08, 0x08);
		else
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x08, 0x00);
	} else {
		if (on)
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x10, 0x10);
		else
			rval = regmap_update_bits(flash->regmap,
						  REG_ENABLE, 0x10, 0x00);
	}
	return rval;
}
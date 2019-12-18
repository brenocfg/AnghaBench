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
struct lm3560_flash {int /*<<< orphan*/  regmap; } ;
typedef  enum lm3560_led_id { ____Placeholder_lm3560_led_id } lm3560_led_id ;

/* Variables and functions */
 int LM3560_LED0 ; 
 unsigned int LM3560_TORCH_BRT_MIN ; 
 int LM3560_TORCH_BRT_uA_TO_REG (unsigned int) ; 
 int /*<<< orphan*/  REG_TORCH_BR ; 
 int lm3560_enable_ctrl (struct lm3560_flash*,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm3560_torch_brt_ctrl(struct lm3560_flash *flash,
				 enum lm3560_led_id led_no, unsigned int brt)
{
	int rval;
	u8 br_bits;

	if (brt < LM3560_TORCH_BRT_MIN)
		return lm3560_enable_ctrl(flash, led_no, false);
	else
		rval = lm3560_enable_ctrl(flash, led_no, true);

	br_bits = LM3560_TORCH_BRT_uA_TO_REG(brt);
	if (led_no == LM3560_LED0)
		rval = regmap_update_bits(flash->regmap,
					  REG_TORCH_BR, 0x07, br_bits);
	else
		rval = regmap_update_bits(flash->regmap,
					  REG_TORCH_BR, 0x38, br_bits << 3);

	return rval;
}
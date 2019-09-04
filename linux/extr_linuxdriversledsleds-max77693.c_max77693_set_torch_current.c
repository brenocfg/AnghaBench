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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct max77693_led_device {int torch_iout_reg; scalar_t__ iout_joint; int /*<<< orphan*/  iout_torch_max; struct regmap* regmap; } ;

/* Variables and functions */
 int FLED1 ; 
 int FLED2 ; 
 int /*<<< orphan*/  MAX77693_LED_REG_ITORCH ; 
 int /*<<< orphan*/  TORCH ; 
 int TORCH_IOUT1_SHIFT ; 
 int TORCH_IOUT2_SHIFT ; 
 int TORCH_IOUT_MASK (int) ; 
 int /*<<< orphan*/  max77693_distribute_currents (struct max77693_led_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int max77693_led_iout_to_reg (int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_set_torch_current(struct max77693_led_device *led,
				int fled_id, u32 micro_amp)
{
	struct regmap *rmap = led->regmap;
	u8 iout1_reg = 0, iout2_reg = 0;
	u32 iout[2];

	max77693_distribute_currents(led, fled_id, TORCH, micro_amp,
					led->iout_torch_max, iout);

	if (fled_id == FLED1 || led->iout_joint) {
		iout1_reg = max77693_led_iout_to_reg(iout[FLED1]);
		led->torch_iout_reg &= TORCH_IOUT_MASK(TORCH_IOUT2_SHIFT);
	}
	if (fled_id == FLED2 || led->iout_joint) {
		iout2_reg = max77693_led_iout_to_reg(iout[FLED2]);
		led->torch_iout_reg &= TORCH_IOUT_MASK(TORCH_IOUT1_SHIFT);
	}

	led->torch_iout_reg |= ((iout1_reg << TORCH_IOUT1_SHIFT) |
				(iout2_reg << TORCH_IOUT2_SHIFT));

	return regmap_write(rmap, MAX77693_LED_REG_ITORCH,
						led->torch_iout_reg);
}
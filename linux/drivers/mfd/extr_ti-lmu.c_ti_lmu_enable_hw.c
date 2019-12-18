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
struct ti_lmu {int /*<<< orphan*/  regmap; scalar_t__ en_gpio; } ;
typedef  enum ti_lmu_id { ____Placeholder_ti_lmu_id } ti_lmu_id ;

/* Variables and functions */
 int LM3631 ; 
 int /*<<< orphan*/  LM3631_LCD_EN_MASK ; 
 int /*<<< orphan*/  LM3631_REG_DEVCTRL ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ti_lmu_enable_hw(struct ti_lmu *lmu, enum ti_lmu_id id)
{
	if (lmu->en_gpio)
		gpiod_set_value(lmu->en_gpio, 1);

	/* Delay about 1ms after HW enable pin control */
	usleep_range(1000, 1500);

	/* LM3631 has additional power up sequence - enable LCD_EN bit. */
	if (id == LM3631) {
		return regmap_update_bits(lmu->regmap, LM3631_REG_DEVCTRL,
					  LM3631_LCD_EN_MASK,
					  LM3631_LCD_EN_MASK);
	}

	return 0;
}
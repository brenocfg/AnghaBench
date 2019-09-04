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
struct st_uvis25_hw {int enabled; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_UVIS25_REG_CTRL1_ADDR ; 
 int /*<<< orphan*/  ST_UVIS25_REG_ODR_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_uvis25_set_enable(struct st_uvis25_hw *hw, bool enable)
{
	int err;

	err = regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL1_ADDR,
				 ST_UVIS25_REG_ODR_MASK, enable);
	if (err < 0)
		return err;

	hw->enabled = enable;

	return 0;
}
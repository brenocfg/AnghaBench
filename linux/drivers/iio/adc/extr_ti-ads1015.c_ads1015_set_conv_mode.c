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
struct ads1015_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS1015_CFG_MOD_MASK ; 
 int ADS1015_CFG_MOD_SHIFT ; 
 int /*<<< orphan*/  ADS1015_CFG_REG ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ads1015_set_conv_mode(struct ads1015_data *data, int mode)
{
	return regmap_update_bits(data->regmap, ADS1015_CFG_REG,
				  ADS1015_CFG_MOD_MASK,
				  mode << ADS1015_CFG_MOD_SHIFT);
}
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
typedef  int u32 ;
struct mlxreg_led_priv_data {int /*<<< orphan*/  access_lock; struct mlxreg_core_platform_data* pdata; } ;
struct mlxreg_led_data {struct mlxreg_core_data* data; struct mlxreg_led_priv_data* data_parent; } ;
struct mlxreg_core_platform_data {int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_data {int mask; int /*<<< orphan*/  reg; scalar_t__ bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rol32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int ror32 (int,scalar_t__) ; 

__attribute__((used)) static int
mlxreg_led_store_hw(struct mlxreg_led_data *led_data, u8 vset)
{
	struct mlxreg_led_priv_data *priv = led_data->data_parent;
	struct mlxreg_core_platform_data *led_pdata = priv->pdata;
	struct mlxreg_core_data *data = led_data->data;
	u32 regval;
	u32 nib;
	int ret;

	/*
	 * Each LED is controlled through low or high nibble of the relevant
	 * register byte. Register offset is specified by off parameter.
	 * Parameter vset provides color code: 0x0 for off, 0x5 for solid red,
	 * 0x6 for 3Hz blink red, 0xd for solid green, 0xe for 3Hz blink
	 * green.
	 * Parameter mask specifies which nibble is used for specific LED: mask
	 * 0xf0 - lower nibble is to be used (bits from 0 to 3), mask 0x0f -
	 * higher nibble (bits from 4 to 7).
	 */
	mutex_lock(&priv->access_lock);

	ret = regmap_read(led_pdata->regmap, data->reg, &regval);
	if (ret)
		goto access_error;

	nib = (ror32(data->mask, data->bit) == 0xf0) ? rol32(vset, data->bit) :
	      rol32(vset, data->bit + 4);
	regval = (regval & data->mask) | nib;

	ret = regmap_write(led_pdata->regmap, data->reg, regval);

access_error:
	mutex_unlock(&priv->access_lock);

	return ret;
}
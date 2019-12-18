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
struct stts751_priv {int config; int res; int interval; int therm; int hyst; int /*<<< orphan*/  event_min; int /*<<< orphan*/  event_max; int /*<<< orphan*/  dev; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int STTS751_CONF_RES_MASK ; 
 int STTS751_CONF_RES_SHIFT ; 
 int /*<<< orphan*/  STTS751_REG_CONF ; 
 int /*<<< orphan*/  STTS751_REG_HLIM_H ; 
 int /*<<< orphan*/  STTS751_REG_HLIM_L ; 
 int /*<<< orphan*/  STTS751_REG_HYST ; 
 int /*<<< orphan*/  STTS751_REG_LLIM_H ; 
 int /*<<< orphan*/  STTS751_REG_LLIM_L ; 
 int /*<<< orphan*/  STTS751_REG_RATE ; 
 int /*<<< orphan*/  STTS751_REG_TLIM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stts751_intervals ; 
 int stts751_read_reg16 (struct stts751_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stts751_read_reg8 (struct stts751_priv*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stts751_read_chip_config(struct stts751_priv *priv)
{
	int ret;
	int tmp;

	ret = i2c_smbus_read_byte_data(priv->client, STTS751_REG_CONF);
	if (ret < 0)
		return ret;
	priv->config = ret;
	priv->res = (ret & STTS751_CONF_RES_MASK) >> STTS751_CONF_RES_SHIFT;

	ret = i2c_smbus_read_byte_data(priv->client, STTS751_REG_RATE);
	if (ret < 0)
		return ret;
	if (ret >= ARRAY_SIZE(stts751_intervals)) {
		dev_err(priv->dev, "Unrecognized conversion rate 0x%x\n", ret);
		return -ENODEV;
	}
	priv->interval = ret;

	ret = stts751_read_reg16(priv, &priv->event_max,
				 STTS751_REG_HLIM_H, STTS751_REG_HLIM_L);
	if (ret)
		return ret;

	ret = stts751_read_reg16(priv, &priv->event_min,
				 STTS751_REG_LLIM_H, STTS751_REG_LLIM_L);
	if (ret)
		return ret;

	ret = stts751_read_reg8(priv, &priv->therm, STTS751_REG_TLIM);
	if (ret)
		return ret;

	ret = stts751_read_reg8(priv, &tmp, STTS751_REG_HYST);
	if (ret)
		return ret;
	priv->hyst = priv->therm - tmp;

	return 0;
}
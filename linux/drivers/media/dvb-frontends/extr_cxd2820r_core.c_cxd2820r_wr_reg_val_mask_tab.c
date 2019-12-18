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
struct regmap {int dummy; } ;
struct reg_val_mask {int reg; unsigned int val; unsigned int mask; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cxd2820r_priv {struct regmap** regmap; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_write (struct regmap*,unsigned int,unsigned int) ; 
 int regmap_write_bits (struct regmap*,unsigned int,unsigned int,unsigned int) ; 

int cxd2820r_wr_reg_val_mask_tab(struct cxd2820r_priv *priv,
				 const struct reg_val_mask *tab, int tab_len)
{
	struct i2c_client *client = priv->client[0];
	int ret;
	unsigned int i, reg, mask, val;
	struct regmap *regmap;

	dev_dbg(&client->dev, "tab_len=%d\n", tab_len);

	for (i = 0; i < tab_len; i++) {
		if ((tab[i].reg >> 16) & 0x1)
			regmap = priv->regmap[1];
		else
			regmap = priv->regmap[0];

		reg = (tab[i].reg >> 0) & 0xffff;
		val = tab[i].val;
		mask = tab[i].mask;

		if (mask == 0xff)
			ret = regmap_write(regmap, reg, val);
		else
			ret = regmap_write_bits(regmap, reg, mask, val);
		if (ret)
			goto error;
	}

	return 0;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct m88ds3103_reg_val {int reg; int /*<<< orphan*/  val; } ;
struct m88ds3103_dev {int /*<<< orphan*/  regmap; TYPE_1__* cfg; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int i2c_wr_max; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int m88ds3103_wr_reg_val_tab(struct m88ds3103_dev *dev,
		const struct m88ds3103_reg_val *tab, int tab_len)
{
	struct i2c_client *client = dev->client;
	int ret, i, j;
	u8 buf[83];

	dev_dbg(&client->dev, "tab_len=%d\n", tab_len);

	if (tab_len > 86) {
		ret = -EINVAL;
		goto err;
	}

	for (i = 0, j = 0; i < tab_len; i++, j++) {
		buf[j] = tab[i].val;

		if (i == tab_len - 1 || tab[i].reg != tab[i + 1].reg - 1 ||
				!((j + 1) % (dev->cfg->i2c_wr_max - 1))) {
			ret = regmap_bulk_write(dev->regmap, tab[i].reg - j, buf, j + 1);
			if (ret)
				goto err;

			j = -1;
		}
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
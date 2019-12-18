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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct e4000_dev {int active; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int e4000_init(struct e4000_dev *dev)
{
	struct i2c_client *client = dev->client;
	int ret;

	dev_dbg(&client->dev, "\n");

	/* reset */
	ret = regmap_write(dev->regmap, 0x00, 0x01);
	if (ret)
		goto err;

	/* disable output clock */
	ret = regmap_write(dev->regmap, 0x06, 0x00);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x7a, 0x96);
	if (ret)
		goto err;

	/* configure gains */
	ret = regmap_bulk_write(dev->regmap, 0x7e, "\x01\xfe", 2);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x82, 0x00);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x24, 0x05);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x87, "\x20\x01", 2);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x9f, "\x7f\x07", 2);
	if (ret)
		goto err;

	/* DC offset control */
	ret = regmap_write(dev->regmap, 0x2d, 0x1f);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x70, "\x01\x01", 2);
	if (ret)
		goto err;

	/* gain control */
	ret = regmap_write(dev->regmap, 0x1a, 0x17);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x1f, 0x1a);
	if (ret)
		goto err;

	dev->active = true;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
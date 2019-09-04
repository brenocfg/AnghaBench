#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct fc2580_dev {int active; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* fc2580_init_reg_vals ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc2580_init(struct fc2580_dev *dev)
{
	struct i2c_client *client = dev->client;
	int ret, i;

	dev_dbg(&client->dev, "\n");

	for (i = 0; i < ARRAY_SIZE(fc2580_init_reg_vals); i++) {
		ret = regmap_write(dev->regmap, fc2580_init_reg_vals[i].reg,
				fc2580_init_reg_vals[i].val);
		if (ret)
			goto err;
	}

	dev->active = true;
	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
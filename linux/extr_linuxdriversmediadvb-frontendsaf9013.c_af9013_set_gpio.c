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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct af9013_state {int /*<<< orphan*/  regmap; struct i2c_client* client; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int af9013_set_gpio(struct af9013_state *state, u8 gpio, u8 gpioval)
{
	struct i2c_client *client = state->client;
	int ret;
	u8 pos;
	u16 addr;

	dev_dbg(&client->dev, "gpio %u, gpioval %02x\n", gpio, gpioval);

	/*
	 * GPIO0 & GPIO1 0xd735
	 * GPIO2 & GPIO3 0xd736
	 */

	switch (gpio) {
	case 0:
	case 1:
		addr = 0xd735;
		break;
	case 2:
	case 3:
		addr = 0xd736;
		break;

	default:
		ret = -EINVAL;
		goto err;
	}

	switch (gpio) {
	case 0:
	case 2:
		pos = 0;
		break;
	case 1:
	case 3:
	default:
		pos = 4;
		break;
	}

	ret = regmap_update_bits(state->regmap, addr, 0x0f << pos,
				 gpioval << pos);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	return ret;
}
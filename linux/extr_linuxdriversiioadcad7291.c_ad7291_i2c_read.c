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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ad7291_chip_info {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7291_i2c_read(struct ad7291_chip_info *chip, u8 reg, u16 *data)
{
	struct i2c_client *client = chip->client;
	int ret = 0;

	ret = i2c_smbus_read_word_swapped(client, reg);
	if (ret < 0) {
		dev_err(&client->dev, "I2C read error\n");
		return ret;
	}

	*data = ret;

	return 0;
}
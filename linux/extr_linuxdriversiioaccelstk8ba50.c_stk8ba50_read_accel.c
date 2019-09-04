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
struct stk8ba50_data {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk8ba50_read_accel(struct stk8ba50_data *data, u8 reg)
{
	int ret;
	struct i2c_client *client = data->client;

	ret = i2c_smbus_read_word_data(client, reg);
	if (ret < 0) {
		dev_err(&client->dev, "register read failed\n");
		return ret;
	}

	return ret;
}
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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADT7316_REG_MAX_ADDR ; 
 int adt7316_i2c_read (struct i2c_client*,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int adt7316_i2c_multi_read(void *client, u8 reg, u8 count, u8 *data)
{
	struct i2c_client *cl = client;
	int i, ret;

	if (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	for (i = 0; i < count; i++) {
		ret = adt7316_i2c_read(cl, reg, &data[i]);
		if (ret < 0) {
			dev_err(&cl->dev, "I2C multi read error\n");
			return ret;
		}
	}

	return 0;
}
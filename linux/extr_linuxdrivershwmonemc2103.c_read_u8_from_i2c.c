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
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static int read_u8_from_i2c(struct i2c_client *client, u8 i2c_reg, u8 *output)
{
	int status = i2c_smbus_read_byte_data(client, i2c_reg);
	if (status < 0) {
		dev_warn(&client->dev, "reg 0x%02x, err %d\n",
			i2c_reg, status);
	} else {
		*output = status;
	}
	return status;
}
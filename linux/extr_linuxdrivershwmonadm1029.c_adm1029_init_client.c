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
 int /*<<< orphan*/  ADM1029_REG_CONFIG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adm1029_init_client(struct i2c_client *client)
{
	u8 config;

	config = i2c_smbus_read_byte_data(client, ADM1029_REG_CONFIG);
	if ((config & 0x10) == 0) {
		i2c_smbus_write_byte_data(client, ADM1029_REG_CONFIG,
					  config | 0x10);
	}
	/* recheck config */
	config = i2c_smbus_read_byte_data(client, ADM1029_REG_CONFIG);
	if ((config & 0x10) == 0) {
		dev_err(&client->dev, "Initialization failed!\n");
		return 0;
	}
	return 1;
}
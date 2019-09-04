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
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_SMBUS_IAP_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int elan_smbus_set_flash_key(struct i2c_client *client)
{
	int error;
	u8 cmd[4] = { 0x00, 0x0B, 0x00, 0x5A };

	error = i2c_smbus_write_block_data(client, ETP_SMBUS_IAP_CMD,
					   sizeof(cmd), cmd);
	if (error) {
		dev_err(&client->dev, "cannot set flash key: %d\n", error);
		return error;
	}

	return 0;
}
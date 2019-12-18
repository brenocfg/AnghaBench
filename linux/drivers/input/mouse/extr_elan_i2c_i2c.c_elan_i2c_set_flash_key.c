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

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_IAP_CMD ; 
 int /*<<< orphan*/  ETP_I2C_IAP_PASSWORD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elan_i2c_write_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_i2c_set_flash_key(struct i2c_client *client)
{
	int error;

	error = elan_i2c_write_cmd(client, ETP_I2C_IAP_CMD,
				   ETP_I2C_IAP_PASSWORD);
	if (error) {
		dev_err(&client->dev, "cannot set flash key: %d\n", error);
		return error;
	}

	return 0;
}
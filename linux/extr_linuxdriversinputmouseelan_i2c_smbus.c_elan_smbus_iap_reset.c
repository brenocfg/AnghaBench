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
 int /*<<< orphan*/  ETP_SMBUS_IAP_RESET_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_smbus_iap_reset(struct i2c_client *client)
{
	int error;

	error = i2c_smbus_write_byte(client, ETP_SMBUS_IAP_RESET_CMD);
	if (error) {
		dev_err(&client->dev, "cannot reset IC: %d\n", error);
		return error;
	}

	return 0;
}
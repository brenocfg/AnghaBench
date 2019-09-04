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
typedef  enum tp_mode { ____Placeholder_tp_mode } tp_mode ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_IAP_CTRL_CMD ; 
 int ETP_I2C_MAIN_MODE_ON ; 
 int IAP_MODE ; 
 int MAIN_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elan_i2c_read_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_i2c_iap_get_mode(struct i2c_client *client, enum tp_mode *mode)
{
	int error;
	u16 constant;
	u8 val[3];

	error = elan_i2c_read_cmd(client, ETP_I2C_IAP_CTRL_CMD, val);
	if (error) {
		dev_err(&client->dev,
			"failed to read iap control register: %d\n",
			error);
		return error;
	}

	constant = le16_to_cpup((__le16 *)val);
	dev_dbg(&client->dev, "iap control reg: 0x%04x.\n", constant);

	*mode = (constant & ETP_I2C_MAIN_MODE_ON) ? MAIN_MODE : IAP_MODE;

	return 0;
}
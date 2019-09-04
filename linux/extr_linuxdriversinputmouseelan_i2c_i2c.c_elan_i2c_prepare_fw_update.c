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
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
typedef  enum tp_mode { ____Placeholder_tp_mode } tp_mode ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ETP_I2C_IAP_CMD ; 
 int ETP_I2C_IAP_PASSWORD ; 
 int IAP_MODE ; 
 int MAIN_MODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int elan_i2c_iap_get_mode (struct i2c_client*,int*) ; 
 int elan_i2c_iap_reset (struct i2c_client*) ; 
 int elan_i2c_read_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int elan_i2c_set_flash_key (struct i2c_client*) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int elan_i2c_prepare_fw_update(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int error;
	enum tp_mode mode;
	u8 val[3];
	u16 password;

	/* Get FW in which mode	(IAP_MODE/MAIN_MODE)  */
	error = elan_i2c_iap_get_mode(client, &mode);
	if (error)
		return error;

	if (mode == IAP_MODE) {
		/* Reset IC */
		error = elan_i2c_iap_reset(client);
		if (error)
			return error;

		msleep(30);
	}

	/* Set flash key*/
	error = elan_i2c_set_flash_key(client);
	if (error)
		return error;

	/* Wait for F/W IAP initialization */
	msleep(mode == MAIN_MODE ? 100 : 30);

	/* Check if we are in IAP mode or not */
	error = elan_i2c_iap_get_mode(client, &mode);
	if (error)
		return error;

	if (mode == MAIN_MODE) {
		dev_err(dev, "wrong mode: %d\n", mode);
		return -EIO;
	}

	/* Set flash key again */
	error = elan_i2c_set_flash_key(client);
	if (error)
		return error;

	/* Wait for F/W IAP initialization */
	msleep(30);

	/* read back to check we actually enabled successfully. */
	error = elan_i2c_read_cmd(client, ETP_I2C_IAP_CMD, val);
	if (error) {
		dev_err(dev, "cannot read iap password: %d\n",
			error);
		return error;
	}

	password = le16_to_cpup((__le16 *)val);
	if (password != ETP_I2C_IAP_PASSWORD) {
		dev_err(dev, "wrong iap password: 0x%X\n", password);
		return -EIO;
	}

	return 0;
}
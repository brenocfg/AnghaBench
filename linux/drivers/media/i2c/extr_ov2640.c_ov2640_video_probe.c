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
struct ov2640_priv {int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_SEL ; 
 int /*<<< orphan*/  BANK_SEL_SENS ; 
 int ENODEV ; 
 int /*<<< orphan*/  MIDH ; 
 int /*<<< orphan*/  MIDL ; 
 int /*<<< orphan*/  PID ; 
#define  PID_OV2640 128 
 int /*<<< orphan*/  VER ; 
 int VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov2640_s_power (int /*<<< orphan*/ *,int) ; 
 struct ov2640_priv* to_ov2640 (struct i2c_client*) ; 

__attribute__((used)) static int ov2640_video_probe(struct i2c_client *client)
{
	struct ov2640_priv *priv = to_ov2640(client);
	u8 pid, ver, midh, midl;
	const char *devname;
	int ret;

	ret = ov2640_s_power(&priv->subdev, 1);
	if (ret < 0)
		return ret;

	/*
	 * check and show product ID and manufacturer ID
	 */
	i2c_smbus_write_byte_data(client, BANK_SEL, BANK_SEL_SENS);
	pid  = i2c_smbus_read_byte_data(client, PID);
	ver  = i2c_smbus_read_byte_data(client, VER);
	midh = i2c_smbus_read_byte_data(client, MIDH);
	midl = i2c_smbus_read_byte_data(client, MIDL);

	switch (VERSION(pid, ver)) {
	case PID_OV2640:
		devname     = "ov2640";
		break;
	default:
		dev_err(&client->dev,
			"Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		goto done;
	}

	dev_info(&client->dev,
		 "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

done:
	ov2640_s_power(&priv->subdev, 0);
	return ret;
}
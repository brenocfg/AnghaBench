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
struct mma9551_version_info {int /*<<< orphan*/ * fw_version; int /*<<< orphan*/  device_id; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  MMA9551_APPID_VERSION ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mma9551_transfer (struct i2c_client*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int mma9551_read_version(struct i2c_client *client)
{
	struct mma9551_version_info info;
	int ret;

	ret = mma9551_transfer(client, MMA9551_APPID_VERSION, 0x00, 0x00,
			       NULL, 0, (u8 *)&info, sizeof(info));
	if (ret < 0)
		return ret;

	dev_info(&client->dev, "device ID 0x%x, firmware version %02x.%02x\n",
		 be32_to_cpu(info.device_id), info.fw_version[0],
		 info.fw_version[1]);

	return 0;
}
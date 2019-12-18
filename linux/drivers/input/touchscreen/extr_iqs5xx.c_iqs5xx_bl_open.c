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
 int EINVAL ; 
 int IQS5XX_BL_ATTEMPTS ; 
 int /*<<< orphan*/  IQS5XX_BL_CMD_VER ; 
 int IQS5XX_NUM_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int iqs5xx_bl_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iqs5xx_reset (struct i2c_client*) ; 

__attribute__((used)) static int iqs5xx_bl_open(struct i2c_client *client)
{
	int error, i, j;

	/*
	 * The device opens a bootloader polling window for 2 ms following the
	 * release of reset. If the host cannot establish communication during
	 * this time frame, it must cycle reset again.
	 */
	for (i = 0; i < IQS5XX_BL_ATTEMPTS; i++) {
		iqs5xx_reset(client);

		for (j = 0; j < IQS5XX_NUM_RETRIES; j++) {
			error = iqs5xx_bl_cmd(client, IQS5XX_BL_CMD_VER, 0);
			if (!error || error == -EINVAL)
				return error;
		}
	}

	dev_err(&client->dev, "Failed to open bootloader: %d\n", error);

	return error;
}
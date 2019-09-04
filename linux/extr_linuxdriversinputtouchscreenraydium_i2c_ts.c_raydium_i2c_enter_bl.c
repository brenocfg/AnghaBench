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
typedef  int /*<<< orphan*/  cal_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  RAYDIUM_ACK_NULL ; 
 int /*<<< orphan*/  RM_BOOT_DELAY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int raydium_i2c_write_object (struct i2c_client*,int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raydium_i2c_enter_bl(struct i2c_client *client)
{
	static const u8 cal_cmd[] = { 0x00, 0x01, 0x52 };
	int error;

	error = raydium_i2c_write_object(client, cal_cmd, sizeof(cal_cmd),
					 RAYDIUM_ACK_NULL);
	if (error) {
		dev_err(&client->dev, "enter bl command failed: %d\n", error);
		return error;
	}

	msleep(RM_BOOT_DELAY_MS);
	return 0;
}
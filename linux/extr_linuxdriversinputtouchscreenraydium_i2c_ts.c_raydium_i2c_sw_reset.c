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
typedef  int /*<<< orphan*/  soft_rst_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  RM_RESET_DELAY_MSEC ; 
 int /*<<< orphan*/  RM_RESET_MSG_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int raydium_i2c_send_message (struct i2c_client*,int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static int raydium_i2c_sw_reset(struct i2c_client *client)
{
	const u8 soft_rst_cmd = 0x01;
	int error;

	error = raydium_i2c_send_message(client, RM_RESET_MSG_ADDR,
					 &soft_rst_cmd, sizeof(soft_rst_cmd));
	if (error) {
		dev_err(&client->dev, "software reset failed: %d\n", error);
		return error;
	}

	msleep(RM_RESET_DELAY_MSEC);

	return 0;
}
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
typedef  scalar_t__ const u8 ;
struct raydium_data {int /*<<< orphan*/  boot_mode; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  RAYDIUM_TS_BLDR ; 
 int /*<<< orphan*/  RAYDIUM_TS_MAIN ; 
 int /*<<< orphan*/  RM_CMD_BOOT_READ ; 
 int raydium_i2c_read (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__ const*,int) ; 

__attribute__((used)) static int raydium_i2c_check_fw_status(struct raydium_data *ts)
{
	struct i2c_client *client = ts->client;
	static const u8 bl_ack = 0x62;
	static const u8 main_ack = 0x66;
	u8 buf[4];
	int error;

	error = raydium_i2c_read(client, RM_CMD_BOOT_READ, buf, sizeof(buf));
	if (!error) {
		if (buf[0] == bl_ack)
			ts->boot_mode = RAYDIUM_TS_BLDR;
		else if (buf[0] == main_ack)
			ts->boot_mode = RAYDIUM_TS_MAIN;
		return 0;
	}

	return error;
}
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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_INF_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int elan_i2c_read_block (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_i2c_read_cmd(struct i2c_client *client, u16 reg, u8 *val)
{
	int retval;

	retval = elan_i2c_read_block(client, reg, val, ETP_I2C_INF_LENGTH);
	if (retval < 0) {
		dev_err(&client->dev, "reading cmd (0x%04x) fail.\n", reg);
		return retval;
	}

	return 0;
}
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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ov9640_reg_read (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ov9640_reg_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov9640_reg_rmw(struct i2c_client *client, u8 reg, u8 set, u8 unset)
{
	u8 val;
	int ret;

	ret = ov9640_reg_read(client, reg, &val);
	if (ret) {
		dev_err(&client->dev,
			"[Read]-Modify-Write of register %02x failed!\n", reg);
		return ret;
	}

	val |= set;
	val &= ~unset;

	ret = ov9640_reg_write(client, reg, val);
	if (ret)
		dev_err(&client->dev,
			"Read-Modify-[Write] of register %02x failed!\n", reg);

	return ret;
}
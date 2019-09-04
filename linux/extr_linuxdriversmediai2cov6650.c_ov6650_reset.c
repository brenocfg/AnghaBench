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
 int /*<<< orphan*/  COMA_RESET ; 
 int /*<<< orphan*/  REG_COMA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ov6650_reg_rmw (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov6650_reset(struct i2c_client *client)
{
	int ret;

	dev_dbg(&client->dev, "reset\n");

	ret = ov6650_reg_rmw(client, REG_COMA, COMA_RESET, 0);
	if (ret)
		dev_err(&client->dev,
			"An error occurred while entering soft reset!\n");

	return ret;
}
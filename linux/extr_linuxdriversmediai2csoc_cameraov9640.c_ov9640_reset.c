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
 int /*<<< orphan*/  OV9640_COM7 ; 
 int /*<<< orphan*/  OV9640_COM7_SCCB_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ov9640_reg_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov9640_reset(struct i2c_client *client)
{
	int ret;

	ret = ov9640_reg_write(client, OV9640_COM7, OV9640_COM7_SCCB_RESET);
	if (ret)
		dev_err(&client->dev,
			"An error occurred while entering soft reset!\n");

	return ret;
}
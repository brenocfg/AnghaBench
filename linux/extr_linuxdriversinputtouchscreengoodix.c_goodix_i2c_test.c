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
 int /*<<< orphan*/  GOODIX_REG_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int goodix_i2c_read (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int goodix_i2c_test(struct i2c_client *client)
{
	int retry = 0;
	int error;
	u8 test;

	while (retry++ < 2) {
		error = goodix_i2c_read(client, GOODIX_REG_ID,
					&test, 1);
		if (!error)
			return 0;

		dev_err(&client->dev, "i2c test failed attempt %d: %d\n",
			retry, error);
		msleep(20);
	}

	return error;
}
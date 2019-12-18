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
typedef  int /*<<< orphan*/  tm ;
struct rtc_time {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  X1205_CCR_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int x1205_set_datetime (struct i2c_client*,struct rtc_time*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x1205_fix_osc(struct i2c_client *client)
{
	int err;
	struct rtc_time tm;

	memset(&tm, 0, sizeof(tm));

	err = x1205_set_datetime(client, &tm, X1205_CCR_BASE, 0);
	if (err < 0)
		dev_err(&client->dev, "unable to restart the oscillator\n");

	return err;
}
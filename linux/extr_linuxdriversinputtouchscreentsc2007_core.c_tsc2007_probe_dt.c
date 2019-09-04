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
struct tsc2007 {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int tsc2007_probe_dt(struct i2c_client *client, struct tsc2007 *ts)
{
	dev_err(&client->dev, "platform data is required!\n");
	return -EINVAL;
}
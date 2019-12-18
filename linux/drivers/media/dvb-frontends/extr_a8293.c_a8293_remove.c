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
struct a8293_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct a8293_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct a8293_dev*) ; 

__attribute__((used)) static int a8293_remove(struct i2c_client *client)
{
	struct a8293_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	kfree(dev);
	return 0;
}
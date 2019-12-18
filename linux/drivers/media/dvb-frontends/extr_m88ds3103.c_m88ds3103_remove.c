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
struct m88ds3103_dev {int /*<<< orphan*/  muxc; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct m88ds3103_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct m88ds3103_dev*) ; 

__attribute__((used)) static int m88ds3103_remove(struct i2c_client *client)
{
	struct m88ds3103_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	i2c_mux_del_adapters(dev->muxc);

	kfree(dev);
	return 0;
}
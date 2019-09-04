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
struct mn88472_dev {int /*<<< orphan*/ * regmap; int /*<<< orphan*/ * client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct mn88472_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mn88472_dev*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mn88472_remove(struct i2c_client *client)
{
	struct mn88472_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	regmap_exit(dev->regmap[2]);
	i2c_unregister_device(dev->client[2]);

	regmap_exit(dev->regmap[1]);
	i2c_unregister_device(dev->client[1]);

	regmap_exit(dev->regmap[0]);

	kfree(dev);

	return 0;
}
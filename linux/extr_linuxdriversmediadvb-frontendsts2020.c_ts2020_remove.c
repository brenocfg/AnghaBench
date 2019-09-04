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
struct ts2020_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  dont_poll; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ts2020_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct ts2020_priv*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts2020_remove(struct i2c_client *client)
{
	struct ts2020_priv *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	/* stop statistics polling */
	if (!dev->dont_poll)
		cancel_delayed_work_sync(&dev->stat_work);

	regmap_exit(dev->regmap);
	kfree(dev);
	return 0;
}
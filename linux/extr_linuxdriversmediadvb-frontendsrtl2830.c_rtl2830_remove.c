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
struct rtl2830_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  muxc; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct rtl2830_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rtl2830_dev*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl2830_remove(struct i2c_client *client)
{
	struct rtl2830_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	i2c_mux_del_adapters(dev->muxc);
	regmap_exit(dev->regmap);
	kfree(dev);

	return 0;
}
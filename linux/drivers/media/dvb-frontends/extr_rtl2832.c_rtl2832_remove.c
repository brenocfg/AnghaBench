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
struct rtl2832_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  muxc; int /*<<< orphan*/  i2c_gate_work; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct rtl2832_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rtl2832_dev*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl2832_remove(struct i2c_client *client)
{
	struct rtl2832_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	cancel_delayed_work_sync(&dev->i2c_gate_work);

	i2c_mux_del_adapters(dev->muxc);

	regmap_exit(dev->regmap);

	kfree(dev);

	return 0;
}
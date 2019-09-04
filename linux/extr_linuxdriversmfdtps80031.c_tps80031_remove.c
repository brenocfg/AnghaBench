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
struct tps80031 {struct i2c_client** clients; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  dev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int TPS80031_NUM_SLAVES ; 
 struct tps80031* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tps80031* tps80031_power_off_dev ; 

__attribute__((used)) static int tps80031_remove(struct i2c_client *client)
{
	struct tps80031 *tps80031 = i2c_get_clientdata(client);
	int i;

	if (tps80031_power_off_dev == tps80031) {
		tps80031_power_off_dev = NULL;
		pm_power_off = NULL;
	}

	mfd_remove_devices(tps80031->dev);

	regmap_del_irq_chip(client->irq, tps80031->irq_data);

	for (i = 0; i < TPS80031_NUM_SLAVES; i++) {
		if (tps80031->clients[i] != client)
			i2c_unregister_device(tps80031->clients[i]);
	}
	return 0;
}
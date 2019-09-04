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
struct tps65090 {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 struct tps65090* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65090_i2c_remove(struct i2c_client *client)
{
	struct tps65090 *tps65090 = i2c_get_clientdata(client);

	mfd_remove_devices(tps65090->dev);
	if (client->irq)
		regmap_del_irq_chip(client->irq, tps65090->irq_data);

	return 0;
}
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
struct tps6586x {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct tps6586x*) ; 
 struct tps6586x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps6586x_remove_subdevs (struct tps6586x*) ; 

__attribute__((used)) static int tps6586x_i2c_remove(struct i2c_client *client)
{
	struct tps6586x *tps6586x = i2c_get_clientdata(client);

	tps6586x_remove_subdevs(tps6586x);
	mfd_remove_devices(tps6586x->dev);
	if (client->irq)
		free_irq(client->irq, tps6586x);
	return 0;
}
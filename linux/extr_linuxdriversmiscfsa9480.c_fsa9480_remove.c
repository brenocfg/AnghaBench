#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; scalar_t__ irq; } ;
struct fsa9480_usbsw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  fsa9480_group ; 
 struct fsa9480_usbsw* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsa9480_remove(struct i2c_client *client)
{
	struct fsa9480_usbsw *usbsw = i2c_get_clientdata(client);

	if (client->irq)
		free_irq(client->irq, usbsw);

	sysfs_remove_group(&client->dev.kobj, &fsa9480_group);
	device_init_wakeup(&client->dev, 0);
	kfree(usbsw);
	return 0;
}
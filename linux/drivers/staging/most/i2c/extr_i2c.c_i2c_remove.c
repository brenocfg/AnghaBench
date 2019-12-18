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
struct i2c_client {int dummy; } ;
struct hdm_i2c {int /*<<< orphan*/  most_iface; } ;

/* Variables and functions */
 struct hdm_i2c* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct hdm_i2c*) ; 
 int /*<<< orphan*/  most_deregister_interface (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_remove(struct i2c_client *client)
{
	struct hdm_i2c *dev = i2c_get_clientdata(client);

	most_deregister_interface(&dev->most_iface);
	kfree(dev);

	return 0;
}
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
struct i2c_hid {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_HID_PWR_SLEEP ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct i2c_hid*) ; 
 struct i2c_hid* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_hid_set_power (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_hid_shutdown(struct i2c_client *client)
{
	struct i2c_hid *ihid = i2c_get_clientdata(client);

	i2c_hid_set_power(client, I2C_HID_PWR_SLEEP);
	free_irq(client->irq, ihid);
}
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
struct i2c_hid {int /*<<< orphan*/  flags; } ;
struct i2c_client {int dummy; } ;
struct hid_device {struct i2c_client* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_HID_STARTED ; 
 struct i2c_hid* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_hid_open(struct hid_device *hid)
{
	struct i2c_client *client = hid->driver_data;
	struct i2c_hid *ihid = i2c_get_clientdata(client);

	set_bit(I2C_HID_STARTED, &ihid->flags);
	return 0;
}
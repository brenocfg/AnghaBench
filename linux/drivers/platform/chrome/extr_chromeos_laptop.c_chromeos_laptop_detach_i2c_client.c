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
struct i2c_peripheral {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int num_i2c_peripherals; struct i2c_peripheral* i2c_peripherals; } ;

/* Variables and functions */
 TYPE_1__* cros_laptop ; 

__attribute__((used)) static void chromeos_laptop_detach_i2c_client(struct i2c_client *client)
{
	struct i2c_peripheral *i2c_dev;
	int i;

	for (i = 0; i < cros_laptop->num_i2c_peripherals; i++) {
		i2c_dev = &cros_laptop->i2c_peripherals[i];

		if (i2c_dev->client == client)
			i2c_dev->client = NULL;
	}
}
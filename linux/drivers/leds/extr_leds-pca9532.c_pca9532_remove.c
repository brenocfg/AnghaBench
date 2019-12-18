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
struct pca9532_data {TYPE_1__* chip_info; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_leds; } ;

/* Variables and functions */
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 int pca9532_destroy_devices (struct pca9532_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca9532_remove(struct i2c_client *client)
{
	struct pca9532_data *data = i2c_get_clientdata(client);
	int err;

	err = pca9532_destroy_devices(data, data->chip_info->num_leds);
	if (err)
		return err;

	return 0;
}
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
struct adc128_data {scalar_t__ regulator; } ;

/* Variables and functions */
 struct adc128_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static int adc128_remove(struct i2c_client *client)
{
	struct adc128_data *data = i2c_get_clientdata(client);

	if (data->regulator)
		regulator_disable(data->regulator);

	return 0;
}
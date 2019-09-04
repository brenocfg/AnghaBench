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
struct adxl34x {int dummy; } ;

/* Variables and functions */
 int adxl34x_remove (struct adxl34x*) ; 
 struct adxl34x* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int adxl34x_i2c_remove(struct i2c_client *client)
{
	struct adxl34x *ac = i2c_get_clientdata(client);

	return adxl34x_remove(ac);
}
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
struct tps65912 {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tps65912* i2c_get_clientdata (struct i2c_client*) ; 
 int tps65912_device_exit (struct tps65912*) ; 

__attribute__((used)) static int tps65912_i2c_remove(struct i2c_client *client)
{
	struct tps65912 *tps = i2c_get_clientdata(client);

	return tps65912_device_exit(tps);
}
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
struct tc3589x {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tc3589x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc3589x_remove(struct i2c_client *client)
{
	struct tc3589x *tc3589x = i2c_get_clientdata(client);

	mfd_remove_devices(tc3589x->dev);

	return 0;
}
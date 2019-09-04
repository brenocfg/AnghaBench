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
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct rpisense {TYPE_1__ joystick; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct rpisense* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpisense_remove(struct i2c_client *i2c)
{
	struct rpisense *rpisense = i2c_get_clientdata(i2c);

	platform_device_unregister(rpisense->joystick.pdev);
	return 0;
}
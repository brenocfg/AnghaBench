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
struct ak881x {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 struct ak881x* to_ak881x (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ak881x_remove(struct i2c_client *client)
{
	struct ak881x *ak881x = to_ak881x(client);

	v4l2_device_unregister_subdev(&ak881x->subdev);

	return 0;
}
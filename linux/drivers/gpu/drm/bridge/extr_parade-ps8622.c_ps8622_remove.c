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
struct ps8622_bridge {int /*<<< orphan*/  bridge; int /*<<< orphan*/  bl; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct ps8622_bridge* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int ps8622_remove(struct i2c_client *client)
{
	struct ps8622_bridge *ps8622 = i2c_get_clientdata(client);

	backlight_device_unregister(ps8622->bl);
	drm_bridge_remove(&ps8622->bridge);

	return 0;
}
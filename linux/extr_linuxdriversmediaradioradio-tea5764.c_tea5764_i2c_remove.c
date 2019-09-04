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
struct tea5764_device {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  vdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (char*) ; 
 struct tea5764_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_power_down (struct tea5764_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tea5764_i2c_remove(struct i2c_client *client)
{
	struct tea5764_device *radio = i2c_get_clientdata(client);

	PDEBUG("remove");
	if (radio) {
		tea5764_power_down(radio);
		video_unregister_device(&radio->vdev);
		v4l2_ctrl_handler_free(&radio->ctrl_handler);
		v4l2_device_unregister(&radio->v4l2_dev);
		kfree(radio);
	}
	return 0;
}
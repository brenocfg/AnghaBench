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
struct v4l2_subdev {int /*<<< orphan*/  entity; int /*<<< orphan*/  ctrl_handler; } ;
struct s5c73m3 {struct v4l2_subdev sensor_sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  s5c73m3_unregister_spi_driver (struct s5c73m3*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5c73m3_remove(struct i2c_client *client)
{
	struct v4l2_subdev *oif_sd = i2c_get_clientdata(client);
	struct s5c73m3 *state = oif_sd_to_s5c73m3(oif_sd);
	struct v4l2_subdev *sensor_sd = &state->sensor_sd;

	v4l2_async_unregister_subdev(oif_sd);

	v4l2_ctrl_handler_free(oif_sd->ctrl_handler);
	media_entity_cleanup(&oif_sd->entity);

	v4l2_device_unregister_subdev(sensor_sd);
	media_entity_cleanup(&sensor_sd->entity);

	s5c73m3_unregister_spi_driver(state);

	return 0;
}
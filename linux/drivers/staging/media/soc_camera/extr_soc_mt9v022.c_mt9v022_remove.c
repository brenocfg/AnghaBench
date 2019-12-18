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
struct soc_camera_subdev_desc {int /*<<< orphan*/  (* free_bus ) (struct soc_camera_subdev_desc*) ;} ;
struct mt9v022 {int /*<<< orphan*/  hdl; int /*<<< orphan*/  subdev; int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (struct soc_camera_subdev_desc*) ; 
 struct mt9v022* to_mt9v022 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9v022_remove(struct i2c_client *client)
{
	struct mt9v022 *mt9v022 = to_mt9v022(client);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);

	v4l2_clk_put(mt9v022->clk);
	v4l2_device_unregister_subdev(&mt9v022->subdev);
	if (ssdd->free_bus)
		ssdd->free_bus(ssdd);
	v4l2_ctrl_handler_free(&mt9v022->hdl);

	return 0;
}
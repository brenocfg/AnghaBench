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
struct rj54n1 {int /*<<< orphan*/  hdl; int /*<<< orphan*/  subdev; int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (struct soc_camera_subdev_desc*) ; 
 struct rj54n1* to_rj54n1 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rj54n1_remove(struct i2c_client *client)
{
	struct rj54n1 *rj54n1 = to_rj54n1(client);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);

	v4l2_clk_put(rj54n1->clk);
	v4l2_device_unregister_subdev(&rj54n1->subdev);
	if (ssdd->free_bus)
		ssdd->free_bus(ssdd);
	v4l2_ctrl_handler_free(&rj54n1->hdl);

	return 0;
}
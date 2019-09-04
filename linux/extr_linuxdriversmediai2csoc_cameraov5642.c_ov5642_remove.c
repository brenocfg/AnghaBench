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
struct ov5642 {int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (struct soc_camera_subdev_desc*) ; 
 struct ov5642* to_ov5642 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5642_remove(struct i2c_client *client)
{
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct ov5642 *priv = to_ov5642(client);

	v4l2_clk_put(priv->clk);
	if (ssdd->free_bus)
		ssdd->free_bus(ssdd);

	return 0;
}
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
struct imx074 {int /*<<< orphan*/  clk; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (struct soc_camera_subdev_desc*) ; 
 struct imx074* to_imx074 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx074_remove(struct i2c_client *client)
{
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct imx074 *priv = to_imx074(client);

	v4l2_async_unregister_subdev(&priv->subdev);
	v4l2_clk_put(priv->clk);

	if (ssdd->free_bus)
		ssdd->free_bus(ssdd);

	return 0;
}
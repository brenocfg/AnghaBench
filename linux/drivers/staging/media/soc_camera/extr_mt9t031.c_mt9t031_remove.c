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
struct mt9t031 {int /*<<< orphan*/  hdl; int /*<<< orphan*/  subdev; int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t031_remove(struct i2c_client *client)
{
	struct mt9t031 *mt9t031 = to_mt9t031(client);

	v4l2_clk_put(mt9t031->clk);
	v4l2_device_unregister_subdev(&mt9t031->subdev);
	v4l2_ctrl_handler_free(&mt9t031->hdl);

	return 0;
}
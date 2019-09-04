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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct mt9m111 {int /*<<< orphan*/  hdl; int /*<<< orphan*/  clk; TYPE_1__ subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_remove(struct i2c_client *client)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);

	v4l2_async_unregister_subdev(&mt9m111->subdev);
	media_entity_cleanup(&mt9m111->subdev.entity);
	v4l2_clk_put(mt9m111->clk);
	v4l2_ctrl_handler_free(&mt9m111->hdl);

	return 0;
}
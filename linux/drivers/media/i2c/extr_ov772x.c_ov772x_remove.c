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
struct ov772x_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  hdl; TYPE_1__ subdev; scalar_t__ pwdn_gpio; int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct ov772x_priv* to_ov772x (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_remove(struct i2c_client *client)
{
	struct ov772x_priv *priv = to_ov772x(i2c_get_clientdata(client));

	media_entity_cleanup(&priv->subdev.entity);
	clk_put(priv->clk);
	if (priv->pwdn_gpio)
		gpiod_put(priv->pwdn_gpio);
	v4l2_async_unregister_subdev(&priv->subdev);
	v4l2_ctrl_handler_free(&priv->hdl);
	mutex_destroy(&priv->lock);

	return 0;
}
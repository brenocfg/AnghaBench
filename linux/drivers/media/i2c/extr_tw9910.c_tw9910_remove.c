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
struct tw9910_priv {int /*<<< orphan*/  subdev; int /*<<< orphan*/  clk; scalar_t__ pdn_gpio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tw9910_remove(struct i2c_client *client)
{
	struct tw9910_priv *priv = to_tw9910(client);

	if (priv->pdn_gpio)
		gpiod_put(priv->pdn_gpio);
	clk_put(priv->clk);
	v4l2_async_unregister_subdev(&priv->subdev);

	return 0;
}
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
struct mt9t112_priv {int /*<<< orphan*/  subdev; int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mt9t112_priv* to_mt9t112 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t112_remove(struct i2c_client *client)
{
	struct mt9t112_priv *priv = to_mt9t112(client);

	clk_disable_unprepare(priv->clk);
	v4l2_async_unregister_subdev(&priv->subdev);

	return 0;
}
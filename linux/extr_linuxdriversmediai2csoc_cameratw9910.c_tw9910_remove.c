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
struct tw9910_priv {int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw9910_remove(struct i2c_client *client)
{
	struct tw9910_priv *priv = to_tw9910(client);
	v4l2_clk_put(priv->clk);
	return 0;
}
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
struct v4l2_subdev {int dummy; } ;
struct ov9640_priv {int /*<<< orphan*/  gpio_power; int /*<<< orphan*/  clk; int /*<<< orphan*/  gpio_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ov9640_priv* to_ov9640_sensor (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_clk_disable (int /*<<< orphan*/ ) ; 
 int v4l2_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov9640_s_power(struct v4l2_subdev *sd, int on)
{
	struct ov9640_priv *priv = to_ov9640_sensor(sd);
	int ret = 0;

	if (on) {
		gpiod_set_value(priv->gpio_power, 1);
		usleep_range(1000, 2000);
		ret = v4l2_clk_enable(priv->clk);
		usleep_range(1000, 2000);
		gpiod_set_value(priv->gpio_reset, 0);
	} else {
		gpiod_set_value(priv->gpio_reset, 1);
		usleep_range(1000, 2000);
		v4l2_clk_disable(priv->clk);
		usleep_range(1000, 2000);
		gpiod_set_value(priv->gpio_power, 0);
	}

	return ret;
}
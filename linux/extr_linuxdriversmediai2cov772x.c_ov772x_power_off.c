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
struct ov772x_priv {scalar_t__ pwdn_gpio; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov772x_power_off(struct ov772x_priv *priv)
{
	clk_disable_unprepare(priv->clk);

	if (priv->pwdn_gpio) {
		gpiod_set_value(priv->pwdn_gpio, 0);
		usleep_range(500, 1000);
	}

	return 0;
}
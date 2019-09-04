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
struct mt9t112_priv {scalar_t__ standby_gpio; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int mt9t112_power_off(struct mt9t112_priv *priv)
{
	clk_disable_unprepare(priv->clk);
	if (priv->standby_gpio) {
		gpiod_set_value(priv->standby_gpio, 1);
		msleep(100);
	}

	return 0;
}
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
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int mt9t112_power_on(struct mt9t112_priv *priv)
{
	int ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	if (priv->standby_gpio) {
		gpiod_set_value(priv->standby_gpio, 0);
		msleep(100);
	}

	return 0;
}
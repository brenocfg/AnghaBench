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
struct tw9910_priv {int /*<<< orphan*/  pdn_gpio; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw9910_set_gpio_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tw9910_power_off(struct tw9910_priv *priv)
{
	clk_disable_unprepare(priv->clk);
	tw9910_set_gpio_value(priv->pdn_gpio, 1);

	return 0;
}
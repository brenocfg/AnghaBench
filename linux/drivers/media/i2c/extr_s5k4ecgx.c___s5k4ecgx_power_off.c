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
struct s5k4ecgx {int /*<<< orphan*/  supplies; scalar_t__ streaming; TYPE_1__* gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 size_t RST ; 
 int /*<<< orphan*/  S5K4ECGX_NUM_SUPPLIES ; 
 size_t STBY ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s5k4ecgx_gpio_set_value (struct s5k4ecgx*,size_t,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __s5k4ecgx_power_off(struct s5k4ecgx *priv)
{
	if (s5k4ecgx_gpio_set_value(priv, RST, !priv->gpio[RST].level))
		usleep_range(30, 50);

	if (s5k4ecgx_gpio_set_value(priv, STBY, !priv->gpio[STBY].level))
		usleep_range(30, 50);

	priv->streaming = 0;

	return regulator_bulk_disable(S5K4ECGX_NUM_SUPPLIES, priv->supplies);
}
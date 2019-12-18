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
struct tda998x_priv {int /*<<< orphan*/  edid_mutex; TYPE_1__* hdmi; struct gpio_desc* calib; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_direction_input (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiod_direction_output (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda998x_cec_set_calibration (struct tda998x_priv*,int) ; 

__attribute__((used)) static void tda998x_cec_calibration(struct tda998x_priv *priv)
{
	struct gpio_desc *calib = priv->calib;

	mutex_lock(&priv->edid_mutex);
	if (priv->hdmi->irq > 0)
		disable_irq(priv->hdmi->irq);
	gpiod_direction_output(calib, 1);
	tda998x_cec_set_calibration(priv, true);

	local_irq_disable();
	gpiod_set_value(calib, 0);
	mdelay(10);
	gpiod_set_value(calib, 1);
	local_irq_enable();

	tda998x_cec_set_calibration(priv, false);
	gpiod_direction_input(calib);
	if (priv->hdmi->irq > 0)
		enable_irq(priv->hdmi->irq);
	mutex_unlock(&priv->edid_mutex);
}
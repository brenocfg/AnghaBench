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
struct tda998x_priv {struct gpio_desc* calib; TYPE_1__* hdmi; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_ASIS ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct gpio_desc* gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda998x_cec_hook_init(void *data)
{
	struct tda998x_priv *priv = data;
	struct gpio_desc *calib;

	calib = gpiod_get(&priv->hdmi->dev, "nxp,calib", GPIOD_ASIS);
	if (IS_ERR(calib)) {
		dev_warn(&priv->hdmi->dev, "failed to get calibration gpio: %ld\n",
			 PTR_ERR(calib));
		return PTR_ERR(calib);
	}

	priv->calib = calib;

	return 0;
}
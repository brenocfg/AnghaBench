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
typedef  int /*<<< orphan*/  u32 ;
struct vsc8531_private {int nleds; int* leds_mode; } ;
struct phy_device {struct vsc8531_private* priv; } ;

/* Variables and functions */
 int sprintf (char*,char*,int) ; 
 int vsc85xx_dt_led_mode_get (struct phy_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc85xx_dt_led_modes_get(struct phy_device *phydev,
				    u32 *default_mode)
{
	struct vsc8531_private *priv = phydev->priv;
	char led_dt_prop[28];
	int i, ret;

	for (i = 0; i < priv->nleds; i++) {
		ret = sprintf(led_dt_prop, "vsc8531,led-%d-mode", i);
		if (ret < 0)
			return ret;

		ret = vsc85xx_dt_led_mode_get(phydev, led_dt_prop,
					      default_mode[i]);
		if (ret < 0)
			return ret;
		priv->leds_mode[i] = ret;
	}

	return 0;
}
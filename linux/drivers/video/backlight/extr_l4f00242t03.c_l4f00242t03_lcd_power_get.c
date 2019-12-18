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
struct lcd_device {int dummy; } ;
struct l4f00242t03_priv {int lcd_state; } ;

/* Variables and functions */
 struct l4f00242t03_priv* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int l4f00242t03_lcd_power_get(struct lcd_device *ld)
{
	struct l4f00242t03_priv *priv = lcd_get_data(ld);

	return priv->lcd_state;
}
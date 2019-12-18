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
struct dcon_priv {int bl_val; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct dcon_priv* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int dcon_bl_get(struct backlight_device *dev)
{
	struct dcon_priv *dcon = bl_get_data(dev);

	return dcon->bl_val;
}
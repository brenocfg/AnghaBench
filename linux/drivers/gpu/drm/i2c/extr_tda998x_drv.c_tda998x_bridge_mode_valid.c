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
struct tda998x_priv {scalar_t__ rev; } ;
struct drm_display_mode {int clock; scalar_t__ htotal; scalar_t__ vtotal; } ;
struct drm_bridge {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int MODE_BAD_HVALUE ; 
 int MODE_BAD_VVALUE ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_OK ; 
 scalar_t__ TDA19988 ; 
 struct tda998x_priv* bridge_to_tda998x_priv (struct drm_bridge*) ; 

__attribute__((used)) static enum drm_mode_status tda998x_bridge_mode_valid(struct drm_bridge *bridge,
				     const struct drm_display_mode *mode)
{
	/* TDA19988 dotclock can go up to 165MHz */
	struct tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	if (mode->clock > ((priv->rev == TDA19988) ? 165000 : 150000))
		return MODE_CLOCK_HIGH;
	if (mode->htotal >= BIT(13))
		return MODE_BAD_HVALUE;
	if (mode->vtotal >= BIT(11))
		return MODE_BAD_VVALUE;
	return MODE_OK;
}
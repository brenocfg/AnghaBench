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
struct drm_psb_private {int display_power; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */

bool gma_power_is_on(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	return dev_priv->display_power;
}
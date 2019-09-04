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
struct drm_psb_private {int /*<<< orphan*/  lvds_bl; int /*<<< orphan*/  lfp_lvds_vbt_mode; int /*<<< orphan*/  sdvo_lvds_vbt_mode; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void psb_intel_destroy_bios(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	kfree(dev_priv->sdvo_lvds_vbt_mode);
	kfree(dev_priv->lfp_lvds_vbt_mode);
	kfree(dev_priv->lvds_bl);
}
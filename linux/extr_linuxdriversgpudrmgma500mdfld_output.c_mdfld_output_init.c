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
struct drm_psb_private {int /*<<< orphan*/  mdfld_panel_id; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI ; 
 int /*<<< orphan*/  TC35876X ; 
 int /*<<< orphan*/  mdfld_init_panel (struct drm_device*,int,int /*<<< orphan*/ ) ; 

int mdfld_output_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	/* FIXME: hardcoded for now */
	dev_priv->mdfld_panel_id = TC35876X;
	/* MIPI panel 1 */
	mdfld_init_panel(dev, 0, dev_priv->mdfld_panel_id);
	/* HDMI panel */
	mdfld_init_panel(dev, 1, HDMI);
	return 0;
}
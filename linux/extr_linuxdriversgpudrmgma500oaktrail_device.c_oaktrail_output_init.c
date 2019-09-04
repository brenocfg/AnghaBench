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
struct drm_psb_private {int /*<<< orphan*/  mode_dev; scalar_t__ hdmi_priv; scalar_t__ iLVDS_enable; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDVOB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  oaktrail_hdmi_init (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oaktrail_lvds_init (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_intel_sdvo_init (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oaktrail_output_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	if (dev_priv->iLVDS_enable)
		oaktrail_lvds_init(dev, &dev_priv->mode_dev);
	else
		dev_err(dev->dev, "DSI is not supported\n");
	if (dev_priv->hdmi_priv)
		oaktrail_hdmi_init(dev, &dev_priv->mode_dev);

	psb_intel_sdvo_init(dev, SDVOB);

	return 0;
}
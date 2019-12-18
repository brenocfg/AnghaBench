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
struct drm_psb_private {int /*<<< orphan*/  mode_dev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_B ; 
 int /*<<< orphan*/  DP_C ; 
 int DP_DETECTED ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDVOB ; 
 int /*<<< orphan*/  SDVOC ; 
 int SDVO_DETECTED ; 
 int /*<<< orphan*/  cdv_disable_vga (struct drm_device*) ; 
 int /*<<< orphan*/  cdv_hdmi_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_crt_init (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdv_intel_dp_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_lvds_init (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_create_scaling_mode_property (struct drm_device*) ; 

__attribute__((used)) static int cdv_output_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	drm_mode_create_scaling_mode_property(dev);

	cdv_disable_vga(dev);

	cdv_intel_crt_init(dev, &dev_priv->mode_dev);
	cdv_intel_lvds_init(dev, &dev_priv->mode_dev);

	/* These bits indicate HDMI not SDVO on CDV */
	if (REG_READ(SDVOB) & SDVO_DETECTED) {
		cdv_hdmi_init(dev, &dev_priv->mode_dev, SDVOB);
		if (REG_READ(DP_B) & DP_DETECTED)
			cdv_intel_dp_init(dev, &dev_priv->mode_dev, DP_B);
	}

	if (REG_READ(SDVOC) & SDVO_DETECTED) {
		cdv_hdmi_init(dev, &dev_priv->mode_dev, SDVOC);
		if (REG_READ(DP_C) & DP_DETECTED)
			cdv_intel_dp_init(dev, &dev_priv->mode_dev, DP_C);
	}
	return 0;
}
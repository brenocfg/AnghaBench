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
struct vmw_private {int capabilities; int /*<<< orphan*/  active_display_unit; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENOSYS ; 
 int SVGA_CAP_GBOBJECTS ; 
 int /*<<< orphan*/  VMWGFX_ENABLE_SCREEN_TARGET_OTABLE ; 
 int VMWGFX_NUM_DISPLAY_UNITS ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_du_screen_target ; 
 int vmw_stdu_init (struct vmw_private*,int) ; 

int vmw_kms_stdu_init_display(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int i, ret;


	/* Do nothing if Screen Target support is turned off */
	if (!VMWGFX_ENABLE_SCREEN_TARGET_OTABLE)
		return -ENOSYS;

	if (!(dev_priv->capabilities & SVGA_CAP_GBOBJECTS))
		return -ENOSYS;

	ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	if (unlikely(ret != 0))
		return ret;

	dev_priv->active_display_unit = vmw_du_screen_target;

	for (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i) {
		ret = vmw_stdu_init(dev_priv, i);

		if (unlikely(ret != 0)) {
			DRM_ERROR("Failed to initialize STDU %d", i);
			return ret;
		}
	}

	DRM_INFO("Screen Target Display device initialized\n");

	return 0;
}
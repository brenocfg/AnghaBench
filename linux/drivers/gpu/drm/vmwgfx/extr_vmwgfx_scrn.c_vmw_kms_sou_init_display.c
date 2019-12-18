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
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int SVGA_CAP_SCREEN_OBJECT_2 ; 
 int VMWGFX_NUM_DISPLAY_UNITS ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_du_screen_object ; 
 int /*<<< orphan*/  vmw_sou_init (struct vmw_private*,int) ; 

int vmw_kms_sou_init_display(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int i, ret;

	if (!(dev_priv->capabilities & SVGA_CAP_SCREEN_OBJECT_2)) {
		DRM_INFO("Not using screen objects,"
			 " missing cap SCREEN_OBJECT_2\n");
		return -ENOSYS;
	}

	ret = -ENOMEM;

	ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	if (unlikely(ret != 0))
		return ret;

	for (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i)
		vmw_sou_init(dev_priv, i);

	dev_priv->active_display_unit = vmw_du_screen_object;

	DRM_INFO("Screen Objects Display Unit initialized\n");

	return 0;
}
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
struct drm_encoder {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void nv04_dfp_update_backlight(struct drm_encoder *encoder, int mode)
{
#ifdef __powerpc__
	struct drm_device *dev = encoder->dev;
	struct nvif_object *device = &nouveau_drm(dev)->client.device.object;

	/* BIOS scripts usually take care of the backlight, thanks
	 * Apple for your consistency.
	 */
	if (dev->pdev->device == 0x0174 || dev->pdev->device == 0x0179 ||
	    dev->pdev->device == 0x0189 || dev->pdev->device == 0x0329) {
		if (mode == DRM_MODE_DPMS_ON) {
			nvif_mask(device, NV_PBUS_DEBUG_DUALHEAD_CTL, 1 << 31, 1 << 31);
			nvif_mask(device, NV_PCRTC_GPIO_EXT, 3, 1);
		} else {
			nvif_mask(device, NV_PBUS_DEBUG_DUALHEAD_CTL, 1 << 31, 0);
			nvif_mask(device, NV_PCRTC_GPIO_EXT, 3, 0);
		}
	}
#endif
}
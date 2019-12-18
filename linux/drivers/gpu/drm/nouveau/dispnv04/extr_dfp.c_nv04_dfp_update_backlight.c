#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvif_object {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {TYPE_3__* pdev; } ;
struct TYPE_5__ {struct nvif_object object; } ;
struct TYPE_6__ {TYPE_1__ device; } ;
struct TYPE_8__ {TYPE_2__ client; } ;
struct TYPE_7__ {int device; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  NV_PBUS_DEBUG_DUALHEAD_CTL ; 
 int /*<<< orphan*/  NV_PCRTC_GPIO_EXT ; 
 TYPE_4__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_mask (struct nvif_object*,int /*<<< orphan*/ ,int,int) ; 

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
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
typedef  int /*<<< orphan*/  wh ;
typedef  int /*<<< orphan*/  u32 ;
struct vc4_dev {int /*<<< orphan*/  firmware; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_FRAMEBUFFER_GET_PHYSICAL_WIDTH_HEIGHT ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static int vc4_fkms_connector_get_modes(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	u32 wh[2] = {0, 0};
	int ret;
	struct drm_display_mode *mode;

	ret = rpi_firmware_property(vc4->firmware,
				    RPI_FIRMWARE_FRAMEBUFFER_GET_PHYSICAL_WIDTH_HEIGHT,
				    &wh, sizeof(wh));
	if (ret) {
		DRM_ERROR("Failed to get screen size: %d (0x%08x 0x%08x)\n",
			  ret, wh[0], wh[1]);
		return 0;
	}

	mode = drm_cvt_mode(dev, wh[0], wh[1], 60 /* vrefresh */,
			    0, 0, false);
	drm_mode_probed_add(connector, mode);

	return 1;
}
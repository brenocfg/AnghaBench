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
struct radeon_device {scalar_t__ family; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int type; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_RS600 ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_add_common_modes (struct drm_encoder*,struct drm_connector*) ; 
 struct drm_encoder* radeon_best_single_encoder (struct drm_connector*) ; 

__attribute__((used)) static int radeon_tv_get_modes(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct drm_display_mode *tv_mode;
	struct drm_encoder *encoder;

	encoder = radeon_best_single_encoder(connector);
	if (!encoder)
		return 0;

	/* avivo chips can scale any mode */
	if (rdev->family >= CHIP_RS600)
		/* add scaled modes */
		radeon_add_common_modes(encoder, connector);
	else {
		/* only 800x600 is supported right now on pre-avivo chips */
		tv_mode = drm_cvt_mode(dev, 800, 600, 60, false, false, false);
		tv_mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, tv_mode);
	}
	return 1;
}
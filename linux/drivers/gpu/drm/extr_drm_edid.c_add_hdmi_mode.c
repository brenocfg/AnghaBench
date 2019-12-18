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
typedef  size_t u8 ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,size_t) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_valid_hdmi_vic (size_t) ; 
 int /*<<< orphan*/ * edid_4k_modes ; 

__attribute__((used)) static int add_hdmi_mode(struct drm_connector *connector, u8 vic)
{
	struct drm_device *dev = connector->dev;
	struct drm_display_mode *newmode;

	if (!drm_valid_hdmi_vic(vic)) {
		DRM_ERROR("Unknown HDMI VIC: %d\n", vic);
		return 0;
	}

	newmode = drm_mode_duplicate(dev, &edid_4k_modes[vic]);
	if (!newmode)
		return 0;

	drm_mode_probed_add(connector, newmode);

	return 1;
}
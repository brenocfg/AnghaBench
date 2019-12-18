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
struct radeon_device {scalar_t__ is_atom_bios; scalar_t__ bios; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_AVIVO (struct radeon_device*) ; 
 int radeon_get_atom_connector_info_from_object_table (struct drm_device*) ; 
 int radeon_get_atom_connector_info_from_supported_devices_table (struct drm_device*) ; 
 int radeon_get_legacy_connector_info_from_bios (struct drm_device*) ; 
 int radeon_get_legacy_connector_info_from_table (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_print_display_setup (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_setup_encoder_clones (struct drm_device*) ; 

__attribute__((used)) static bool radeon_setup_enc_conn(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	bool ret = false;

	if (rdev->bios) {
		if (rdev->is_atom_bios) {
			ret = radeon_get_atom_connector_info_from_supported_devices_table(dev);
			if (ret == false)
				ret = radeon_get_atom_connector_info_from_object_table(dev);
		} else {
			ret = radeon_get_legacy_connector_info_from_bios(dev);
			if (ret == false)
				ret = radeon_get_legacy_connector_info_from_table(dev);
		}
	} else {
		if (!ASIC_IS_AVIVO(rdev))
			ret = radeon_get_legacy_connector_info_from_table(dev);
	}
	if (ret) {
		radeon_setup_encoder_clones(dev);
		radeon_print_display_setup(dev);
	}

	return ret;
}
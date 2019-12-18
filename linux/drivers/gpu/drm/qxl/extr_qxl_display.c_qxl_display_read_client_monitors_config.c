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
struct drm_device {int dummy; } ;
struct qxl_device {struct drm_device ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int MONITORS_CONFIG_BAD_CRC ; 
 int MONITORS_CONFIG_ERROR ; 
 int MONITORS_CONFIG_UNCHANGED ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int qxl_display_copy_rom_client_monitors_config (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_update_offset_props (struct qxl_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void qxl_display_read_client_monitors_config(struct qxl_device *qdev)
{
	struct drm_device *dev = &qdev->ddev;
	int status, retries;

	for (retries = 0; retries < 10; retries++) {
		status = qxl_display_copy_rom_client_monitors_config(qdev);
		if (status != MONITORS_CONFIG_BAD_CRC)
			break;
		udelay(5);
	}
	if (status == MONITORS_CONFIG_ERROR) {
		DRM_DEBUG_KMS("ignoring client monitors config: error");
		return;
	}
	if (status == MONITORS_CONFIG_BAD_CRC) {
		DRM_DEBUG_KMS("ignoring client monitors config: bad crc");
		return;
	}
	if (status == MONITORS_CONFIG_UNCHANGED) {
		DRM_DEBUG_KMS("ignoring client monitors config: unchanged");
		return;
	}

	drm_modeset_lock_all(dev);
	qxl_update_offset_props(qdev);
	drm_modeset_unlock_all(dev);
	if (!drm_helper_hpd_irq_event(dev)) {
		/* notify that the monitor configuration changed, to
		   adjust at the arbitrary resolution */
		drm_kms_helper_hotplug_event(dev);
	}
}
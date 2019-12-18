#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_property {int dummy; } ;
struct TYPE_3__ {struct drm_property* scaling_mode_property; } ;
struct drm_device {TYPE_1__ mode_config; struct amdgpu_device* dev_private; } ;
struct drm_connector_state {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
struct dm_connector_state {int scaling; int /*<<< orphan*/  abm_level; int /*<<< orphan*/  underscan_enable; int /*<<< orphan*/  underscan_vborder; int /*<<< orphan*/  underscan_hborder; } ;
struct TYPE_4__ {struct drm_property* abm_level_property; struct drm_property* underscan_property; struct drm_property* underscan_vborder_property; struct drm_property* underscan_hborder_property; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_SCALE_ASPECT ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_CENTER ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_FULLSCREEN ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_NONE ; 
 int EINVAL ; 
#define  RMX_ASPECT 131 
#define  RMX_CENTER 130 
#define  RMX_FULL 129 
#define  RMX_OFF 128 
 struct dm_connector_state* to_dm_connector_state (struct drm_connector_state const*) ; 

int amdgpu_dm_connector_atomic_get_property(struct drm_connector *connector,
					    const struct drm_connector_state *state,
					    struct drm_property *property,
					    uint64_t *val)
{
	struct drm_device *dev = connector->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct dm_connector_state *dm_state =
		to_dm_connector_state(state);
	int ret = -EINVAL;

	if (property == dev->mode_config.scaling_mode_property) {
		switch (dm_state->scaling) {
		case RMX_CENTER:
			*val = DRM_MODE_SCALE_CENTER;
			break;
		case RMX_ASPECT:
			*val = DRM_MODE_SCALE_ASPECT;
			break;
		case RMX_FULL:
			*val = DRM_MODE_SCALE_FULLSCREEN;
			break;
		case RMX_OFF:
		default:
			*val = DRM_MODE_SCALE_NONE;
			break;
		}
		ret = 0;
	} else if (property == adev->mode_info.underscan_hborder_property) {
		*val = dm_state->underscan_hborder;
		ret = 0;
	} else if (property == adev->mode_info.underscan_vborder_property) {
		*val = dm_state->underscan_vborder;
		ret = 0;
	} else if (property == adev->mode_info.underscan_property) {
		*val = dm_state->underscan_enable;
		ret = 0;
	} else if (property == adev->mode_info.abm_level_property) {
		*val = dm_state->abm_level;
		ret = 0;
	}

	return ret;
}
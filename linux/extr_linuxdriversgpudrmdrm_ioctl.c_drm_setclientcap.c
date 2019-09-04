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
struct drm_set_client_cap {int capability; int value; } ;
struct drm_file {int stereo_allowed; int universal_planes; int atomic; int aspect_ratio_allowed; int writeback_connectors; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
#define  DRM_CLIENT_CAP_ASPECT_RATIO 132 
#define  DRM_CLIENT_CAP_ATOMIC 131 
#define  DRM_CLIENT_CAP_STEREO_3D 130 
#define  DRM_CLIENT_CAP_UNIVERSAL_PLANES 129 
#define  DRM_CLIENT_CAP_WRITEBACK_CONNECTORS 128 
 int EINVAL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
drm_setclientcap(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_set_client_cap *req = data;

	switch (req->capability) {
	case DRM_CLIENT_CAP_STEREO_3D:
		if (req->value > 1)
			return -EINVAL;
		file_priv->stereo_allowed = req->value;
		break;
	case DRM_CLIENT_CAP_UNIVERSAL_PLANES:
		if (req->value > 1)
			return -EINVAL;
		file_priv->universal_planes = req->value;
		break;
	case DRM_CLIENT_CAP_ATOMIC:
		if (!drm_core_check_feature(dev, DRIVER_ATOMIC))
			return -EINVAL;
		if (req->value > 1)
			return -EINVAL;
		file_priv->atomic = req->value;
		file_priv->universal_planes = req->value;
		/*
		 * No atomic user-space blows up on aspect ratio mode bits.
		 */
		file_priv->aspect_ratio_allowed = req->value;
		break;
	case DRM_CLIENT_CAP_ASPECT_RATIO:
		if (req->value > 1)
			return -EINVAL;
		file_priv->aspect_ratio_allowed = req->value;
		break;
	case DRM_CLIENT_CAP_WRITEBACK_CONNECTORS:
		if (!file_priv->atomic)
			return -EINVAL;
		if (req->value > 1)
			return -EINVAL;
		file_priv->writeback_connectors = req->value;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
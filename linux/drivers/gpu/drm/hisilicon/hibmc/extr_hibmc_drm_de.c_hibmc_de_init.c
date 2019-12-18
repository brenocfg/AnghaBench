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
struct hibmc_drm_private {struct drm_device* dev; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_plane*) ; 
 int PTR_ERR (struct drm_plane*) ; 
 struct drm_crtc* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_mode_crtc_set_gamma_size (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  hibmc_crtc_funcs ; 
 int /*<<< orphan*/  hibmc_crtc_helper_funcs ; 
 struct drm_plane* hibmc_plane_init (struct hibmc_drm_private*) ; 

int hibmc_de_init(struct hibmc_drm_private *priv)
{
	struct drm_device *dev = priv->dev;
	struct drm_crtc *crtc;
	struct drm_plane *plane;
	int ret;

	plane = hibmc_plane_init(priv);
	if (IS_ERR(plane)) {
		DRM_ERROR("failed to create plane: %ld\n", PTR_ERR(plane));
		return PTR_ERR(plane);
	}

	crtc = devm_kzalloc(dev->dev, sizeof(*crtc), GFP_KERNEL);
	if (!crtc) {
		DRM_ERROR("failed to alloc memory when init crtc\n");
		return -ENOMEM;
	}

	ret = drm_crtc_init_with_planes(dev, crtc, plane,
					NULL, &hibmc_crtc_funcs, NULL);
	if (ret) {
		DRM_ERROR("failed to init crtc: %d\n", ret);
		return ret;
	}

	ret = drm_mode_crtc_set_gamma_size(crtc, 256);
	if (ret) {
		DRM_ERROR("failed to set gamma size: %d\n", ret);
		return ret;
	}
	drm_crtc_helper_add(crtc, &hibmc_crtc_helper_funcs);

	return 0;
}
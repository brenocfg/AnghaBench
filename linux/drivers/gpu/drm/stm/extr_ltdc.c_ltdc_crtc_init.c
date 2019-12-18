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
struct TYPE_4__ {unsigned int nb_layers; } ;
struct ltdc_device {TYPE_2__ caps; } ;
struct drm_plane {int dummy; } ;
struct drm_device {struct ltdc_device* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUT_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  drm_crtc_enable_color_mgmt (struct drm_crtc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltdc_crtc_funcs ; 
 int /*<<< orphan*/  ltdc_crtc_helper_funcs ; 
 struct drm_plane* ltdc_plane_create (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltdc_plane_destroy_all (struct drm_device*) ; 

__attribute__((used)) static int ltdc_crtc_init(struct drm_device *ddev, struct drm_crtc *crtc)
{
	struct ltdc_device *ldev = ddev->dev_private;
	struct drm_plane *primary, *overlay;
	unsigned int i;
	int ret;

	primary = ltdc_plane_create(ddev, DRM_PLANE_TYPE_PRIMARY);
	if (!primary) {
		DRM_ERROR("Can not create primary plane\n");
		return -EINVAL;
	}

	ret = drm_crtc_init_with_planes(ddev, crtc, primary, NULL,
					&ltdc_crtc_funcs, NULL);
	if (ret) {
		DRM_ERROR("Can not initialize CRTC\n");
		goto cleanup;
	}

	drm_crtc_helper_add(crtc, &ltdc_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(crtc, CLUT_SIZE);
	drm_crtc_enable_color_mgmt(crtc, 0, false, CLUT_SIZE);

	DRM_DEBUG_DRIVER("CRTC:%d created\n", crtc->base.id);

	/* Add planes. Note : the first layer is used by primary plane */
	for (i = 1; i < ldev->caps.nb_layers; i++) {
		overlay = ltdc_plane_create(ddev, DRM_PLANE_TYPE_OVERLAY);
		if (!overlay) {
			ret = -ENOMEM;
			DRM_ERROR("Can not create overlay plane %d\n", i);
			goto cleanup;
		}
	}

	return 0;

cleanup:
	ltdc_plane_destroy_all(ddev);
	return ret;
}
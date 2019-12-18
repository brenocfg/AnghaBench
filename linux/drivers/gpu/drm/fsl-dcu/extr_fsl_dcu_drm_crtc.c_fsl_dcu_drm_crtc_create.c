#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_crtc {int dummy; } ;
struct fsl_dcu_drm_device {int /*<<< orphan*/  drm; struct drm_crtc crtc; } ;
struct drm_plane {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct drm_plane*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (int /*<<< orphan*/ ,struct drm_crtc*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_dcu_drm_crtc_funcs ; 
 int /*<<< orphan*/  fsl_dcu_drm_crtc_helper_funcs ; 
 int /*<<< orphan*/  fsl_dcu_drm_init_planes (int /*<<< orphan*/ ) ; 
 struct drm_plane* fsl_dcu_drm_primary_create_plane (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_plane*) ; 

int fsl_dcu_drm_crtc_create(struct fsl_dcu_drm_device *fsl_dev)
{
	struct drm_plane *primary;
	struct drm_crtc *crtc = &fsl_dev->crtc;
	int ret;

	fsl_dcu_drm_init_planes(fsl_dev->drm);

	primary = fsl_dcu_drm_primary_create_plane(fsl_dev->drm);
	if (!primary)
		return -ENOMEM;

	ret = drm_crtc_init_with_planes(fsl_dev->drm, crtc, primary, NULL,
					&fsl_dcu_drm_crtc_funcs, NULL);
	if (ret) {
		primary->funcs->destroy(primary);
		return ret;
	}

	drm_crtc_helper_add(crtc, &fsl_dcu_drm_crtc_helper_funcs);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; TYPE_2__* funcs; } ;
struct amdgpu_plane {TYPE_3__ base; } ;
struct amdgpu_display_manager {TYPE_1__* adev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* reset ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  DRM_PLANE_TYPE_CURSOR 130 
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int EPERM ; 
 int /*<<< orphan*/  cursor_formats ; 
 int /*<<< orphan*/  dm_plane_funcs ; 
 int /*<<< orphan*/  dm_plane_helper_funcs ; 
 int /*<<< orphan*/  drm_plane_helper_add (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ ,TYPE_3__*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rgb_formats ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  yuv_formats ; 

__attribute__((used)) static int amdgpu_dm_plane_init(struct amdgpu_display_manager *dm,
				struct amdgpu_plane *aplane,
				unsigned long possible_crtcs)
{
	int res = -EPERM;

	switch (aplane->base.type) {
	case DRM_PLANE_TYPE_PRIMARY:
		res = drm_universal_plane_init(
				dm->adev->ddev,
				&aplane->base,
				possible_crtcs,
				&dm_plane_funcs,
				rgb_formats,
				ARRAY_SIZE(rgb_formats),
				NULL, aplane->base.type, NULL);
		break;
	case DRM_PLANE_TYPE_OVERLAY:
		res = drm_universal_plane_init(
				dm->adev->ddev,
				&aplane->base,
				possible_crtcs,
				&dm_plane_funcs,
				yuv_formats,
				ARRAY_SIZE(yuv_formats),
				NULL, aplane->base.type, NULL);
		break;
	case DRM_PLANE_TYPE_CURSOR:
		res = drm_universal_plane_init(
				dm->adev->ddev,
				&aplane->base,
				possible_crtcs,
				&dm_plane_funcs,
				cursor_formats,
				ARRAY_SIZE(cursor_formats),
				NULL, aplane->base.type, NULL);
		break;
	}

	drm_plane_helper_add(&aplane->base, &dm_plane_helper_funcs);

	/* Create (reset) the plane state */
	if (aplane->base.funcs->reset)
		aplane->base.funcs->reset(&aplane->base);


	return res;
}
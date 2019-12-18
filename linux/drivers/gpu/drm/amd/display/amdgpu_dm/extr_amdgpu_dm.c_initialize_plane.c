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
struct drm_plane {int type; } ;
struct dc_plane_cap {int dummy; } ;
struct amdgpu_mode_info {struct drm_plane** planes; } ;
struct amdgpu_display_manager {TYPE_2__* dc; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_3__ {int max_streams; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amdgpu_dm_plane_init (struct amdgpu_display_manager*,struct drm_plane*,unsigned long,struct dc_plane_cap const*) ; 
 int /*<<< orphan*/  kfree (struct drm_plane*) ; 
 struct drm_plane* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int initialize_plane(struct amdgpu_display_manager *dm,
			    struct amdgpu_mode_info *mode_info, int plane_id,
			    enum drm_plane_type plane_type,
			    const struct dc_plane_cap *plane_cap)
{
	struct drm_plane *plane;
	unsigned long possible_crtcs;
	int ret = 0;

	plane = kzalloc(sizeof(struct drm_plane), GFP_KERNEL);
	if (!plane) {
		DRM_ERROR("KMS: Failed to allocate plane\n");
		return -ENOMEM;
	}
	plane->type = plane_type;

	/*
	 * HACK: IGT tests expect that the primary plane for a CRTC
	 * can only have one possible CRTC. Only expose support for
	 * any CRTC if they're not going to be used as a primary plane
	 * for a CRTC - like overlay or underlay planes.
	 */
	possible_crtcs = 1 << plane_id;
	if (plane_id >= dm->dc->caps.max_streams)
		possible_crtcs = 0xff;

	ret = amdgpu_dm_plane_init(dm, plane, possible_crtcs, plane_cap);

	if (ret) {
		DRM_ERROR("KMS: Failed to initialize plane\n");
		kfree(plane);
		return ret;
	}

	if (mode_info)
		mode_info->planes[plane_id] = plane;

	return ret;
}
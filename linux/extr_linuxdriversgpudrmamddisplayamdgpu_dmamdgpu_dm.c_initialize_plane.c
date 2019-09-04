#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct amdgpu_plane {TYPE_1__ base; } ;
struct amdgpu_mode_info {struct amdgpu_plane** planes; int /*<<< orphan*/ * plane_type; } ;
struct amdgpu_display_manager {TYPE_3__* dc; } ;
struct TYPE_5__ {int max_streams; } ;
struct TYPE_6__ {TYPE_2__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amdgpu_dm_plane_init (struct amdgpu_display_manager*,struct amdgpu_plane*,unsigned long) ; 
 struct amdgpu_plane* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int initialize_plane(struct amdgpu_display_manager *dm,
			     struct amdgpu_mode_info *mode_info,
			     int plane_id)
{
	struct amdgpu_plane *plane;
	unsigned long possible_crtcs;
	int ret = 0;

	plane = kzalloc(sizeof(struct amdgpu_plane), GFP_KERNEL);
	mode_info->planes[plane_id] = plane;

	if (!plane) {
		DRM_ERROR("KMS: Failed to allocate plane\n");
		return -ENOMEM;
	}
	plane->base.type = mode_info->plane_type[plane_id];

	/*
	 * HACK: IGT tests expect that each plane can only have one
	 * one possible CRTC. For now, set one CRTC for each
	 * plane that is not an underlay, but still allow multiple
	 * CRTCs for underlay planes.
	 */
	possible_crtcs = 1 << plane_id;
	if (plane_id >= dm->dc->caps.max_streams)
		possible_crtcs = 0xff;

	ret = amdgpu_dm_plane_init(dm, mode_info->planes[plane_id], possible_crtcs);

	if (ret) {
		DRM_ERROR("KMS: Failed to initialize plane\n");
		return ret;
	}

	return ret;
}
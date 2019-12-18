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
typedef  int /*<<< orphan*/  uint32_t ;
struct ww_acquire_ctx {int dummy; } ;
struct ttm_validate_buffer {int num_shared; int /*<<< orphan*/  head; TYPE_2__* bo; } ;
struct list_head {int dummy; } ;
struct drm_plane_state {TYPE_1__* fb; } ;
struct drm_plane {scalar_t__ type; struct drm_plane_state* state; } ;
struct drm_gem_object {int dummy; } ;
struct dm_plane_state {struct dc_plane_state* dc_state; } ;
struct dc_plane_state {int /*<<< orphan*/  address; int /*<<< orphan*/  dcc; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  rotation; int /*<<< orphan*/  format; } ;
struct amdgpu_framebuffer {int /*<<< orphan*/  address; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_2__ tbo; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {struct drm_gem_object** obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ DRM_PLANE_TYPE_CURSOR ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  amdgpu_bo_get_tiling_flags (struct amdgpu_bo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_ref (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_display_supported_domains (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_alloc_gart (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fill_plane_buffer_attributes (struct amdgpu_device*,struct amdgpu_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 struct amdgpu_framebuffer* to_amdgpu_framebuffer (TYPE_1__*) ; 
 struct dm_plane_state* to_dm_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int ttm_eu_reserve_buffers (struct ww_acquire_ctx*,struct list_head*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dm_plane_helper_prepare_fb(struct drm_plane *plane,
				      struct drm_plane_state *new_state)
{
	struct amdgpu_framebuffer *afb;
	struct drm_gem_object *obj;
	struct amdgpu_device *adev;
	struct amdgpu_bo *rbo;
	struct dm_plane_state *dm_plane_state_new, *dm_plane_state_old;
	struct list_head list;
	struct ttm_validate_buffer tv;
	struct ww_acquire_ctx ticket;
	uint64_t tiling_flags;
	uint32_t domain;
	int r;

	dm_plane_state_old = to_dm_plane_state(plane->state);
	dm_plane_state_new = to_dm_plane_state(new_state);

	if (!new_state->fb) {
		DRM_DEBUG_DRIVER("No FB bound\n");
		return 0;
	}

	afb = to_amdgpu_framebuffer(new_state->fb);
	obj = new_state->fb->obj[0];
	rbo = gem_to_amdgpu_bo(obj);
	adev = amdgpu_ttm_adev(rbo->tbo.bdev);
	INIT_LIST_HEAD(&list);

	tv.bo = &rbo->tbo;
	tv.num_shared = 1;
	list_add(&tv.head, &list);

	r = ttm_eu_reserve_buffers(&ticket, &list, false, NULL, true);
	if (r) {
		dev_err(adev->dev, "fail to reserve bo (%d)\n", r);
		return r;
	}

	if (plane->type != DRM_PLANE_TYPE_CURSOR)
		domain = amdgpu_display_supported_domains(adev, rbo->flags);
	else
		domain = AMDGPU_GEM_DOMAIN_VRAM;

	r = amdgpu_bo_pin(rbo, domain);
	if (unlikely(r != 0)) {
		if (r != -ERESTARTSYS)
			DRM_ERROR("Failed to pin framebuffer with error %d\n", r);
		ttm_eu_backoff_reservation(&ticket, &list);
		return r;
	}

	r = amdgpu_ttm_alloc_gart(&rbo->tbo);
	if (unlikely(r != 0)) {
		amdgpu_bo_unpin(rbo);
		ttm_eu_backoff_reservation(&ticket, &list);
		DRM_ERROR("%p bind failed\n", rbo);
		return r;
	}

	amdgpu_bo_get_tiling_flags(rbo, &tiling_flags);

	ttm_eu_backoff_reservation(&ticket, &list);

	afb->address = amdgpu_bo_gpu_offset(rbo);

	amdgpu_bo_ref(rbo);

	if (dm_plane_state_new->dc_state &&
			dm_plane_state_old->dc_state != dm_plane_state_new->dc_state) {
		struct dc_plane_state *plane_state = dm_plane_state_new->dc_state;

		fill_plane_buffer_attributes(
			adev, afb, plane_state->format, plane_state->rotation,
			tiling_flags, &plane_state->tiling_info,
			&plane_state->plane_size, &plane_state->dcc,
			&plane_state->address);
	}

	return 0;
}
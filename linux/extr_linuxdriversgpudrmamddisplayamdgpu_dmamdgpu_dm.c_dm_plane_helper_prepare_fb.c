#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
struct drm_plane_state {TYPE_7__* fb; } ;
struct drm_plane {scalar_t__ type; struct drm_plane_state* state; } ;
struct drm_gem_object {int dummy; } ;
struct dm_plane_state {struct dc_plane_state* dc_state; } ;
struct TYPE_12__ {void* high_part; void* low_part; } ;
struct TYPE_11__ {void* high_part; void* low_part; } ;
struct TYPE_13__ {TYPE_4__ chroma_addr; TYPE_3__ luma_addr; } ;
struct TYPE_9__ {void* high_part; void* low_part; } ;
struct TYPE_10__ {TYPE_1__ addr; } ;
struct TYPE_14__ {TYPE_5__ video_progressive; int /*<<< orphan*/  type; TYPE_2__ grph; } ;
struct dc_plane_state {scalar_t__ format; TYPE_6__ address; } ;
struct amdgpu_framebuffer {scalar_t__ address; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_8__ tbo; } ;
struct TYPE_15__ {int height; int /*<<< orphan*/  width; struct drm_gem_object** obj; } ;

/* Variables and functions */
 unsigned int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ DRM_PLANE_TYPE_CURSOR ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PLN_ADDR_TYPE_VIDEO_PROGRESSIVE ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 scalar_t__ amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_ref (struct amdgpu_bo*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_display_supported_domains (struct amdgpu_device*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_alloc_gart (TYPE_8__*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 void* lower_32_bits (scalar_t__) ; 
 struct amdgpu_framebuffer* to_amdgpu_framebuffer (TYPE_7__*) ; 
 struct dm_plane_state* to_dm_plane_state (struct drm_plane_state*) ; 
 scalar_t__ unlikely (int) ; 
 void* upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int dm_plane_helper_prepare_fb(struct drm_plane *plane,
				      struct drm_plane_state *new_state)
{
	struct amdgpu_framebuffer *afb;
	struct drm_gem_object *obj;
	struct amdgpu_device *adev;
	struct amdgpu_bo *rbo;
	uint64_t chroma_addr = 0;
	struct dm_plane_state *dm_plane_state_new, *dm_plane_state_old;
	unsigned int awidth;
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
	r = amdgpu_bo_reserve(rbo, false);
	if (unlikely(r != 0))
		return r;

	if (plane->type != DRM_PLANE_TYPE_CURSOR)
		domain = amdgpu_display_supported_domains(adev);
	else
		domain = AMDGPU_GEM_DOMAIN_VRAM;

	r = amdgpu_bo_pin(rbo, domain);
	if (unlikely(r != 0)) {
		if (r != -ERESTARTSYS)
			DRM_ERROR("Failed to pin framebuffer with error %d\n", r);
		amdgpu_bo_unreserve(rbo);
		return r;
	}

	r = amdgpu_ttm_alloc_gart(&rbo->tbo);
	if (unlikely(r != 0)) {
		amdgpu_bo_unpin(rbo);
		amdgpu_bo_unreserve(rbo);
		DRM_ERROR("%p bind failed\n", rbo);
		return r;
	}
	amdgpu_bo_unreserve(rbo);

	afb->address = amdgpu_bo_gpu_offset(rbo);

	amdgpu_bo_ref(rbo);

	if (dm_plane_state_new->dc_state &&
			dm_plane_state_old->dc_state != dm_plane_state_new->dc_state) {
		struct dc_plane_state *plane_state = dm_plane_state_new->dc_state;

		if (plane_state->format < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) {
			plane_state->address.grph.addr.low_part = lower_32_bits(afb->address);
			plane_state->address.grph.addr.high_part = upper_32_bits(afb->address);
		} else {
			awidth = ALIGN(new_state->fb->width, 64);
			plane_state->address.type = PLN_ADDR_TYPE_VIDEO_PROGRESSIVE;
			plane_state->address.video_progressive.luma_addr.low_part
							= lower_32_bits(afb->address);
			plane_state->address.video_progressive.luma_addr.high_part
							= upper_32_bits(afb->address);
			chroma_addr = afb->address + (u64)awidth * new_state->fb->height;
			plane_state->address.video_progressive.chroma_addr.low_part
							= lower_32_bits(chroma_addr);
			plane_state->address.video_progressive.chroma_addr.high_part
							= upper_32_bits(chroma_addr);
		}
	}

	return 0;
}
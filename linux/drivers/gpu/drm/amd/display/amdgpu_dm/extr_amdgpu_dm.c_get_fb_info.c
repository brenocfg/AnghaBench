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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * obj; } ;
struct amdgpu_framebuffer {TYPE_1__ base; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  amdgpu_bo_get_tiling_flags (struct amdgpu_bo*,int /*<<< orphan*/ *) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int get_fb_info(const struct amdgpu_framebuffer *amdgpu_fb,
		       uint64_t *tiling_flags)
{
	struct amdgpu_bo *rbo = gem_to_amdgpu_bo(amdgpu_fb->base.obj[0]);
	int r = amdgpu_bo_reserve(rbo, false);

	if (unlikely(r)) {
		/* Don't show error message when returning -ERESTARTSYS */
		if (r != -ERESTARTSYS)
			DRM_ERROR("Unable to reserve buffer: %d\n", r);
		return r;
	}

	if (tiling_flags)
		amdgpu_bo_get_tiling_flags(rbo, tiling_flags);

	amdgpu_bo_unreserve(rbo);

	return r;
}
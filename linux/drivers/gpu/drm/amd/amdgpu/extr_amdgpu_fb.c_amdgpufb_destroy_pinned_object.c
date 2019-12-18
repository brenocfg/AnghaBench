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
struct drm_gem_object {int dummy; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_kunmap (struct amdgpu_bo*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void amdgpufb_destroy_pinned_object(struct drm_gem_object *gobj)
{
	struct amdgpu_bo *abo = gem_to_amdgpu_bo(gobj);
	int ret;

	ret = amdgpu_bo_reserve(abo, true);
	if (likely(ret == 0)) {
		amdgpu_bo_kunmap(abo);
		amdgpu_bo_unpin(abo);
		amdgpu_bo_unreserve(abo);
	}
	drm_gem_object_put_unlocked(gobj);
}
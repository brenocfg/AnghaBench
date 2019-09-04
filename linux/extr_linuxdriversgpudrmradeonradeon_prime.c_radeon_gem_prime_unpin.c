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
struct radeon_bo {scalar_t__ prime_shared_count; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 scalar_t__ unlikely (int) ; 

void radeon_gem_prime_unpin(struct drm_gem_object *obj)
{
	struct radeon_bo *bo = gem_to_radeon_bo(obj);
	int ret = 0;

	ret = radeon_bo_reserve(bo, false);
	if (unlikely(ret != 0))
		return;

	radeon_bo_unpin(bo);
	if (bo->prime_shared_count)
		bo->prime_shared_count--;
	radeon_bo_unreserve(bo);
}
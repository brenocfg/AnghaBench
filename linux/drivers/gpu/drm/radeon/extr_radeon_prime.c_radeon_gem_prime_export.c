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
struct TYPE_2__ {int /*<<< orphan*/  ttm; } ;
struct radeon_bo {TYPE_1__ tbo; } ;
struct drm_gem_object {int dummy; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct dma_buf* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dma_buf* drm_gem_prime_export (struct drm_gem_object*,int) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 scalar_t__ radeon_ttm_tt_has_userptr (int /*<<< orphan*/ ) ; 

struct dma_buf *radeon_gem_prime_export(struct drm_gem_object *gobj,
					int flags)
{
	struct radeon_bo *bo = gem_to_radeon_bo(gobj);
	if (radeon_ttm_tt_has_userptr(bo->tbo.ttm))
		return ERR_PTR(-EPERM);
	return drm_gem_prime_export(gobj, flags);
}
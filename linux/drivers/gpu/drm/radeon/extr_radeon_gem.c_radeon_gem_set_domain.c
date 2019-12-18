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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct radeon_bo {scalar_t__ prime_shared_count; TYPE_2__ tbo; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 long EBUSY ; 
 long EINTR ; 
 int EINVAL ; 
 int HZ ; 
 scalar_t__ RADEON_GEM_DOMAIN_CPU ; 
 scalar_t__ RADEON_GEM_DOMAIN_VRAM ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,int) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int radeon_gem_set_domain(struct drm_gem_object *gobj,
			  uint32_t rdomain, uint32_t wdomain)
{
	struct radeon_bo *robj;
	uint32_t domain;
	long r;

	/* FIXME: reeimplement */
	robj = gem_to_radeon_bo(gobj);
	/* work out where to validate the buffer to */
	domain = wdomain;
	if (!domain) {
		domain = rdomain;
	}
	if (!domain) {
		/* Do nothings */
		pr_warn("Set domain without domain !\n");
		return 0;
	}
	if (domain == RADEON_GEM_DOMAIN_CPU) {
		/* Asking for cpu access wait for object idle */
		r = dma_resv_wait_timeout_rcu(robj->tbo.base.resv, true, true, 30 * HZ);
		if (!r)
			r = -EBUSY;

		if (r < 0 && r != -EINTR) {
			pr_err("Failed to wait for object: %li\n", r);
			return r;
		}
	}
	if (domain == RADEON_GEM_DOMAIN_VRAM && robj->prime_shared_count) {
		/* A BO that is associated with a dma-buf cannot be sensibly migrated to VRAM */
		return -EINVAL;
	}
	return 0;
}
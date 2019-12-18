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
typedef  int uint64_t ;
typedef  int u64 ;
struct msm_gpu {int dummy; } ;
struct msm_gem_address_space {char const* name; int /*<<< orphan*/  kref; int /*<<< orphan*/  mm; int /*<<< orphan*/  mmu; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_gem_address_space* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct msm_gem_address_space* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gpummu_new (struct device*,struct msm_gpu*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct msm_gem_address_space *
msm_gem_address_space_create_a2xx(struct device *dev, struct msm_gpu *gpu,
		const char *name, uint64_t va_start, uint64_t va_end)
{
	struct msm_gem_address_space *aspace;
	u64 size = va_end - va_start;

	aspace = kzalloc(sizeof(*aspace), GFP_KERNEL);
	if (!aspace)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&aspace->lock);
	aspace->name = name;
	aspace->mmu = msm_gpummu_new(dev, gpu);

	drm_mm_init(&aspace->mm, (va_start >> PAGE_SHIFT),
		size >> PAGE_SHIFT);

	kref_init(&aspace->kref);

	return aspace;
}
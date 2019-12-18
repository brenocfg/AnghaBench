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
typedef  int u32 ;
struct v3d_dev {int /*<<< orphan*/  pt_paddr; scalar_t__ pt; int /*<<< orphan*/  dev; int /*<<< orphan*/  mm; int /*<<< orphan*/  cache_clean_lock; int /*<<< orphan*/  sched_lock; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  bo_lock; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  mm_lock; TYPE_1__* queue; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fence_context; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int V3D_MAX_QUEUES ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dma_alloc_wc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 
 int /*<<< orphan*/  v3d_init_hw_state (struct v3d_dev*) ; 
 int /*<<< orphan*/  v3d_mmu_set_page_table (struct v3d_dev*) ; 
 int v3d_sched_init (struct v3d_dev*) ; 

int
v3d_gem_init(struct drm_device *dev)
{
	struct v3d_dev *v3d = to_v3d_dev(dev);
	u32 pt_size = 4096 * 1024;
	int ret, i;

	for (i = 0; i < V3D_MAX_QUEUES; i++)
		v3d->queue[i].fence_context = dma_fence_context_alloc(1);

	spin_lock_init(&v3d->mm_lock);
	spin_lock_init(&v3d->job_lock);
	mutex_init(&v3d->bo_lock);
	mutex_init(&v3d->reset_lock);
	mutex_init(&v3d->sched_lock);
	mutex_init(&v3d->cache_clean_lock);

	/* Note: We don't allocate address 0.  Various bits of HW
	 * treat 0 as special, such as the occlusion query counters
	 * where 0 means "disabled".
	 */
	drm_mm_init(&v3d->mm, 1, pt_size / sizeof(u32) - 1);

	v3d->pt = dma_alloc_wc(v3d->dev, pt_size,
			       &v3d->pt_paddr,
			       GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
	if (!v3d->pt) {
		drm_mm_takedown(&v3d->mm);
		dev_err(v3d->dev,
			"Failed to allocate page tables. "
			"Please ensure you have CMA enabled.\n");
		return -ENOMEM;
	}

	v3d_init_hw_state(v3d);
	v3d_mmu_set_page_table(v3d);

	ret = v3d_sched_init(v3d);
	if (ret) {
		drm_mm_takedown(&v3d->mm);
		dma_free_coherent(v3d->dev, 4096 * 1024, (void *)v3d->pt,
				  v3d->pt_paddr);
	}

	return 0;
}
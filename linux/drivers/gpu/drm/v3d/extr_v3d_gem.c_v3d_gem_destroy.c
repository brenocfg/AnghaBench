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
struct v3d_dev {int /*<<< orphan*/  pt_paddr; scalar_t__ pt; int /*<<< orphan*/  dev; int /*<<< orphan*/  mm; int /*<<< orphan*/  render_job; int /*<<< orphan*/  bin_job; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 
 int /*<<< orphan*/  v3d_sched_fini (struct v3d_dev*) ; 

void
v3d_gem_destroy(struct drm_device *dev)
{
	struct v3d_dev *v3d = to_v3d_dev(dev);

	v3d_sched_fini(v3d);

	/* Waiting for jobs to finish would need to be done before
	 * unregistering V3D.
	 */
	WARN_ON(v3d->bin_job);
	WARN_ON(v3d->render_job);

	drm_mm_takedown(&v3d->mm);

	dma_free_coherent(v3d->dev, 4096 * 1024, (void *)v3d->pt, v3d->pt_paddr);
}
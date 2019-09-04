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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  reset_work; } ;
struct vc4_dev {TYPE_2__ purgeable; int /*<<< orphan*/  power_lock; int /*<<< orphan*/  job_done_work; TYPE_1__ hangcheck; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  seqno_cb_list; int /*<<< orphan*/  job_done_list; int /*<<< orphan*/  render_job_list; int /*<<< orphan*/  bin_job_list; int /*<<< orphan*/  dma_fence_context; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_hangcheck_elapsed ; 
 int /*<<< orphan*/  vc4_job_done_work ; 
 int /*<<< orphan*/  vc4_reset_work ; 

void
vc4_gem_init(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	vc4->dma_fence_context = dma_fence_context_alloc(1);

	INIT_LIST_HEAD(&vc4->bin_job_list);
	INIT_LIST_HEAD(&vc4->render_job_list);
	INIT_LIST_HEAD(&vc4->job_done_list);
	INIT_LIST_HEAD(&vc4->seqno_cb_list);
	spin_lock_init(&vc4->job_lock);

	INIT_WORK(&vc4->hangcheck.reset_work, vc4_reset_work);
	timer_setup(&vc4->hangcheck.timer, vc4_hangcheck_elapsed, 0);

	INIT_WORK(&vc4->job_done_work, vc4_job_done_work);

	mutex_init(&vc4->power_lock);

	INIT_LIST_HEAD(&vc4->purgeable.list);
	mutex_init(&vc4->purgeable.lock);
}
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
struct vc4_exec_info {scalar_t__ perfmon; int /*<<< orphan*/ * fence; int /*<<< orphan*/  head; } ;
struct vc4_dev {int /*<<< orphan*/  job_done_work; int /*<<< orphan*/  job_wait_queue; int /*<<< orphan*/  job_done_list; int /*<<< orphan*/  finished_seqno; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_signal_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 struct vc4_exec_info* vc4_first_bin_job (struct vc4_dev*) ; 
 struct vc4_exec_info* vc4_first_render_job (struct vc4_dev*) ; 
 int /*<<< orphan*/  vc4_perfmon_stop (struct vc4_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  vc4_submit_next_bin_job (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_submit_next_render_job (struct drm_device*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vc4_irq_finish_render_job(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_exec_info *exec = vc4_first_render_job(vc4);
	struct vc4_exec_info *nextbin, *nextrender;

	if (!exec)
		return;

	vc4->finished_seqno++;
	list_move_tail(&exec->head, &vc4->job_done_list);

	nextbin = vc4_first_bin_job(vc4);
	nextrender = vc4_first_render_job(vc4);

	/* Only stop the perfmon if following jobs in the queue don't expect it
	 * to be enabled.
	 */
	if (exec->perfmon && !nextrender &&
	    (!nextbin || nextbin->perfmon != exec->perfmon))
		vc4_perfmon_stop(vc4, exec->perfmon, true);

	/* If there's a render job waiting, start it. If this is not the case
	 * we may have to unblock the binner if it's been stalled because of
	 * perfmon (this can be checked by comparing the perfmon attached to
	 * the finished renderjob to the one attached to the next bin job: if
	 * they don't match, this means the binner is stalled and should be
	 * restarted).
	 */
	if (nextrender)
		vc4_submit_next_render_job(dev);
	else if (nextbin && nextbin->perfmon != exec->perfmon)
		vc4_submit_next_bin_job(dev);

	if (exec->fence) {
		dma_fence_signal_locked(exec->fence);
		dma_fence_put(exec->fence);
		exec->fence = NULL;
	}

	wake_up_all(&vc4->job_wait_queue);
	schedule_work(&vc4->job_done_work);
}
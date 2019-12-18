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
struct mm_struct {int dummy; } ;
struct kfd_process {scalar_t__ last_eviction_seqno; unsigned long last_restore_timestamp; int /*<<< orphan*/  eviction_work; } ;
struct dma_fence {scalar_t__ seqno; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PROCESS_ACTIVE_TIME_MS ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 unsigned long get_jiffies_64 () ; 
 struct kfd_process* kfd_lookup_process_by_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  kfd_unref_process (struct kfd_process*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

int kgd2kfd_schedule_evict_and_restore_process(struct mm_struct *mm,
					       struct dma_fence *fence)
{
	struct kfd_process *p;
	unsigned long active_time;
	unsigned long delay_jiffies = msecs_to_jiffies(PROCESS_ACTIVE_TIME_MS);

	if (!fence)
		return -EINVAL;

	if (dma_fence_is_signaled(fence))
		return 0;

	p = kfd_lookup_process_by_mm(mm);
	if (!p)
		return -ENODEV;

	if (fence->seqno == p->last_eviction_seqno)
		goto out;

	p->last_eviction_seqno = fence->seqno;

	/* Avoid KFD process starvation. Wait for at least
	 * PROCESS_ACTIVE_TIME_MS before evicting the process again
	 */
	active_time = get_jiffies_64() - p->last_restore_timestamp;
	if (delay_jiffies > active_time)
		delay_jiffies -= active_time;
	else
		delay_jiffies = 0;

	/* During process initialization eviction_work.dwork is initialized
	 * to kfd_evict_bo_worker
	 */
	schedule_delayed_work(&p->eviction_work, delay_jiffies);
out:
	kfd_unref_process(p);
	return 0;
}
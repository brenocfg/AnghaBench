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
typedef  scalar_t__ u64 ;
struct misc_stats {int /*<<< orphan*/  corr_work_done; int /*<<< orphan*/  max_isr_time_ms; int /*<<< orphan*/  max_isr_jiffies; } ;
struct TYPE_2__ {struct misc_stats misc_stats; } ;
struct fnic {unsigned int wq_copy_count; unsigned int raw_wq_count; unsigned int rq_count; int /*<<< orphan*/ * cq; TYPE_1__ fnic_stats; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  fnic_fcpio_cmpl_handler ; 
 scalar_t__ jiffies ; 
 scalar_t__ jiffies_to_msecs (scalar_t__) ; 
 unsigned int vnic_cq_copy_service (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int fnic_wq_copy_cmpl_handler(struct fnic *fnic, int copy_work_to_do)
{
	unsigned int wq_work_done = 0;
	unsigned int i, cq_index;
	unsigned int cur_work_done;
	struct misc_stats *misc_stats = &fnic->fnic_stats.misc_stats;
	u64 start_jiffies = 0;
	u64 end_jiffies = 0;
	u64 delta_jiffies = 0;
	u64 delta_ms = 0;

	for (i = 0; i < fnic->wq_copy_count; i++) {
		cq_index = i + fnic->raw_wq_count + fnic->rq_count;

		start_jiffies = jiffies;
		cur_work_done = vnic_cq_copy_service(&fnic->cq[cq_index],
						     fnic_fcpio_cmpl_handler,
						     copy_work_to_do);
		end_jiffies = jiffies;

		wq_work_done += cur_work_done;
		delta_jiffies = end_jiffies - start_jiffies;
		if (delta_jiffies >
			(u64) atomic64_read(&misc_stats->max_isr_jiffies)) {
			atomic64_set(&misc_stats->max_isr_jiffies,
					delta_jiffies);
			delta_ms = jiffies_to_msecs(delta_jiffies);
			atomic64_set(&misc_stats->max_isr_time_ms, delta_ms);
			atomic64_set(&misc_stats->corr_work_done,
					cur_work_done);
		}
	}
	return wq_work_done;
}
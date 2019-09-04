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
struct wr_log_entry {scalar_t__ opcode; int post_sge_ts; int cqe_sge_ts; int poll_sge_ts; int /*<<< orphan*/  poll_host_time; int /*<<< orphan*/  post_host_time; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  qid; scalar_t__ valid; } ;
struct seq_file {struct c4iw_dev* private; } ;
struct TYPE_3__ {int cclk_ps; } ;
struct TYPE_4__ {int wr_log_size; struct wr_log_entry* wr_log; TYPE_1__ lldi; int /*<<< orphan*/  wr_log_idx; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ FW_RI_RECEIVE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  div64_u64 (int,int) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wr_log_show(struct seq_file *seq, void *v)
{
	struct c4iw_dev *dev = seq->private;
	ktime_t prev_time;
	struct wr_log_entry *lep;
	int prev_time_set = 0;
	int idx, end;

#define ts2ns(ts) div64_u64((ts) * dev->rdev.lldi.cclk_ps, 1000)

	idx = atomic_read(&dev->rdev.wr_log_idx) &
		(dev->rdev.wr_log_size - 1);
	end = idx - 1;
	if (end < 0)
		end = dev->rdev.wr_log_size - 1;
	lep = &dev->rdev.wr_log[idx];
	while (idx != end) {
		if (lep->valid) {
			if (!prev_time_set) {
				prev_time_set = 1;
				prev_time = lep->poll_host_time;
			}
			seq_printf(seq, "%04u: nsec %llu qid %u opcode "
				   "%u %s 0x%x host_wr_delta nsec %llu "
				   "post_sge_ts 0x%llx cqe_sge_ts 0x%llx "
				   "poll_sge_ts 0x%llx post_poll_delta_ns %llu "
				   "cqe_poll_delta_ns %llu\n",
				   idx,
				   ktime_to_ns(ktime_sub(lep->poll_host_time,
							 prev_time)),
				   lep->qid, lep->opcode,
				   lep->opcode == FW_RI_RECEIVE ?
							"msn" : "wrid",
				   lep->wr_id,
				   ktime_to_ns(ktime_sub(lep->poll_host_time,
							 lep->post_host_time)),
				   lep->post_sge_ts, lep->cqe_sge_ts,
				   lep->poll_sge_ts,
				   ts2ns(lep->poll_sge_ts - lep->post_sge_ts),
				   ts2ns(lep->poll_sge_ts - lep->cqe_sge_ts));
			prev_time = lep->poll_host_time;
		}
		idx++;
		if (idx > (dev->rdev.wr_log_size - 1))
			idx = 0;
		lep = &dev->rdev.wr_log[idx];
	}
#undef ts2ns
	return 0;
}
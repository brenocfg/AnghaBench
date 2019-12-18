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
struct sdebug_queued_cmd {struct sdebug_defer* sd_dp; TYPE_2__* a_cmnd; } ;
struct sdebug_queue {int /*<<< orphan*/  qc_lock; int /*<<< orphan*/  in_use_bm; struct sdebug_queued_cmd* qc_arr; } ;
struct sdebug_dev_info {int /*<<< orphan*/  num_in_q; } ;
struct sdebug_defer {int defer_t; } ;
typedef  enum sdeb_defer_type { ____Placeholder_sdeb_defer_type } sdeb_defer_type ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int SDEBUG_CANQUEUE ; 
 void* SDEB_DEFER_NONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 struct sdebug_queue* sdebug_q_arr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_qc_helper (struct sdebug_defer*,int) ; 
 int submit_queues ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_all_queued(void)
{
	unsigned long iflags;
	int j, k;
	enum sdeb_defer_type l_defer_t;
	struct sdebug_queue *sqp;
	struct sdebug_queued_cmd *sqcp;
	struct sdebug_dev_info *devip;
	struct sdebug_defer *sd_dp;

	for (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) {
		spin_lock_irqsave(&sqp->qc_lock, iflags);
		for (k = 0; k < SDEBUG_CANQUEUE; ++k) {
			if (test_bit(k, sqp->in_use_bm)) {
				sqcp = &sqp->qc_arr[k];
				if (sqcp->a_cmnd == NULL)
					continue;
				devip = (struct sdebug_dev_info *)
					sqcp->a_cmnd->device->hostdata;
				if (devip)
					atomic_dec(&devip->num_in_q);
				sqcp->a_cmnd = NULL;
				sd_dp = sqcp->sd_dp;
				if (sd_dp) {
					l_defer_t = sd_dp->defer_t;
					sd_dp->defer_t = SDEB_DEFER_NONE;
				} else
					l_defer_t = SDEB_DEFER_NONE;
				spin_unlock_irqrestore(&sqp->qc_lock, iflags);
				stop_qc_helper(sd_dp, l_defer_t);
				clear_bit(k, sqp->in_use_bm);
				spin_lock_irqsave(&sqp->qc_lock, iflags);
			}
		}
		spin_unlock_irqrestore(&sqp->qc_lock, iflags);
	}
}
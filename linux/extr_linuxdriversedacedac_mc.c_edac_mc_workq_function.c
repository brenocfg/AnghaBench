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
struct work_struct {int dummy; } ;
struct mem_ctl_info {scalar_t__ op_state; int /*<<< orphan*/  work; int /*<<< orphan*/  (* edac_check ) (struct mem_ctl_info*) ;} ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 scalar_t__ EDAC_OPSTATE_POLL ; 
 scalar_t__ OP_RUNNING_POLL ; 
 int /*<<< orphan*/  edac_mc_get_poll_msec () ; 
 scalar_t__ edac_op_state ; 
 int /*<<< orphan*/  edac_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_ctls_mutex ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mem_ctl_info*) ; 
 struct delayed_work* to_delayed_work (struct work_struct*) ; 
 struct mem_ctl_info* to_edac_mem_ctl_work (struct delayed_work*) ; 

__attribute__((used)) static void edac_mc_workq_function(struct work_struct *work_req)
{
	struct delayed_work *d_work = to_delayed_work(work_req);
	struct mem_ctl_info *mci = to_edac_mem_ctl_work(d_work);

	mutex_lock(&mem_ctls_mutex);

	if (mci->op_state != OP_RUNNING_POLL) {
		mutex_unlock(&mem_ctls_mutex);
		return;
	}

	if (edac_op_state == EDAC_OPSTATE_POLL)
		mci->edac_check(mci);

	mutex_unlock(&mem_ctls_mutex);

	/* Queue ourselves again. */
	edac_queue_work(&mci->work, msecs_to_jiffies(edac_mc_get_poll_msec()));
}
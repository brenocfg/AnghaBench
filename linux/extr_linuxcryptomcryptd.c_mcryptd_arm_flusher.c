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
struct mcryptd_flush_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct mcryptd_alg_cstate {int flusher_engaged; int /*<<< orphan*/  flush; scalar_t__ next_flush; int /*<<< orphan*/  flush_list; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kcrypto_wq ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcryptd_flist ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mcryptd_flush_list* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void mcryptd_arm_flusher(struct mcryptd_alg_cstate *cstate, unsigned long delay)
{
	struct mcryptd_flush_list *flist;

	if (!cstate->flusher_engaged) {
		/* put the flusher on the flush list */
		flist = per_cpu_ptr(mcryptd_flist, smp_processor_id());
		mutex_lock(&flist->lock);
		list_add_tail(&cstate->flush_list, &flist->list);
		cstate->flusher_engaged = true;
		cstate->next_flush = jiffies + delay;
		queue_delayed_work_on(smp_processor_id(), kcrypto_wq,
			&cstate->flush, delay);
		mutex_unlock(&flist->lock);
	}
}
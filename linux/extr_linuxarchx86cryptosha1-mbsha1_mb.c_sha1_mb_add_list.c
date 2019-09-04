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
struct TYPE_2__ {unsigned long arrival; unsigned long expire; scalar_t__ seq_num; } ;
struct mcryptd_hash_request_ctx {int /*<<< orphan*/  waiter; TYPE_1__ tag; } ;
struct mcryptd_alg_cstate {int /*<<< orphan*/  work_lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  next_seq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_INTERVAL ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcryptd_arm_flusher (struct mcryptd_alg_cstate*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sha1_mb_add_list(struct mcryptd_hash_request_ctx *rctx,
			     struct mcryptd_alg_cstate *cstate)
{
	unsigned long next_flush;
	unsigned long delay = usecs_to_jiffies(FLUSH_INTERVAL);

	/* initialize tag */
	rctx->tag.arrival = jiffies;    /* tag the arrival time */
	rctx->tag.seq_num = cstate->next_seq_num++;
	next_flush = rctx->tag.arrival + delay;
	rctx->tag.expire = next_flush;

	spin_lock(&cstate->work_lock);
	list_add_tail(&rctx->waiter, &cstate->work_list);
	spin_unlock(&cstate->work_lock);

	mcryptd_arm_flusher(cstate, delay);
}
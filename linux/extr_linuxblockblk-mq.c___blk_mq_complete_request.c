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
struct TYPE_4__ {scalar_t__ flags; struct request* info; int /*<<< orphan*/  func; } ;
struct request {int internal_tag; TYPE_1__* q; TYPE_2__ csd; struct blk_mq_ctx* mq_ctx; } ;
struct blk_mq_ctx {int cpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* softirq_done_fn ) (struct request*) ;int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_SAME_COMP ; 
 int /*<<< orphan*/  QUEUE_FLAG_SAME_FORCE ; 
 int /*<<< orphan*/  __blk_mq_complete_request_remote ; 
 int /*<<< orphan*/  blk_mq_mark_complete (struct request*) ; 
 int /*<<< orphan*/  blk_mq_sched_completed_request (struct request*) ; 
 scalar_t__ cpu_online (int) ; 
 int cpus_share_cache (int,int) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_single_async (int,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct request*) ; 
 int /*<<< orphan*/  stub2 (struct request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __blk_mq_complete_request(struct request *rq)
{
	struct blk_mq_ctx *ctx = rq->mq_ctx;
	bool shared = false;
	int cpu;

	if (!blk_mq_mark_complete(rq))
		return;
	if (rq->internal_tag != -1)
		blk_mq_sched_completed_request(rq);

	if (!test_bit(QUEUE_FLAG_SAME_COMP, &rq->q->queue_flags)) {
		rq->q->softirq_done_fn(rq);
		return;
	}

	cpu = get_cpu();
	if (!test_bit(QUEUE_FLAG_SAME_FORCE, &rq->q->queue_flags))
		shared = cpus_share_cache(cpu, ctx->cpu);

	if (cpu != ctx->cpu && !shared && cpu_online(ctx->cpu)) {
		rq->csd.func = __blk_mq_complete_request_remote;
		rq->csd.info = rq;
		rq->csd.flags = 0;
		smp_call_function_single_async(ctx->cpu, &rq->csd);
	} else {
		rq->q->softirq_done_fn(rq);
	}
	put_cpu();
}
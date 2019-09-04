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
struct TYPE_2__ {scalar_t__ parent; } ;
struct bfq_queue {TYPE_1__ entity; struct bfq_queue* new_bfqq; } ;
struct bfq_data {int busy_queues; struct bfq_queue oom_bfqq; int /*<<< orphan*/  in_serv_last_pos; struct bfq_queue* in_service_queue; } ;

/* Variables and functions */
 struct bfq_queue* bfq_find_close_cooperator (struct bfq_data*,struct bfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_io_struct_pos (void*,int) ; 
 scalar_t__ bfq_may_be_close_cooperator (struct bfq_queue*,struct bfq_queue*) ; 
 scalar_t__ bfq_rq_close_to_sector (void*,int,int /*<<< orphan*/ ) ; 
 struct bfq_queue* bfq_setup_merge (struct bfq_queue*,struct bfq_queue*) ; 
 scalar_t__ bfq_too_late_for_merging (struct bfq_queue*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct bfq_queue *
bfq_setup_cooperator(struct bfq_data *bfqd, struct bfq_queue *bfqq,
		     void *io_struct, bool request)
{
	struct bfq_queue *in_service_bfqq, *new_bfqq;

	/*
	 * Prevent bfqq from being merged if it has been created too
	 * long ago. The idea is that true cooperating processes, and
	 * thus their associated bfq_queues, are supposed to be
	 * created shortly after each other. This is the case, e.g.,
	 * for KVM/QEMU and dump I/O threads. Basing on this
	 * assumption, the following filtering greatly reduces the
	 * probability that two non-cooperating processes, which just
	 * happen to do close I/O for some short time interval, have
	 * their queues merged by mistake.
	 */
	if (bfq_too_late_for_merging(bfqq))
		return NULL;

	if (bfqq->new_bfqq)
		return bfqq->new_bfqq;

	if (!io_struct || unlikely(bfqq == &bfqd->oom_bfqq))
		return NULL;

	/* If there is only one backlogged queue, don't search. */
	if (bfqd->busy_queues == 1)
		return NULL;

	in_service_bfqq = bfqd->in_service_queue;

	if (in_service_bfqq && in_service_bfqq != bfqq &&
	    likely(in_service_bfqq != &bfqd->oom_bfqq) &&
	    bfq_rq_close_to_sector(io_struct, request,
				   bfqd->in_serv_last_pos) &&
	    bfqq->entity.parent == in_service_bfqq->entity.parent &&
	    bfq_may_be_close_cooperator(bfqq, in_service_bfqq)) {
		new_bfqq = bfq_setup_merge(bfqq, in_service_bfqq);
		if (new_bfqq)
			return new_bfqq;
	}
	/*
	 * Check whether there is a cooperator among currently scheduled
	 * queues. The only thing we need is that the bio/request is not
	 * NULL, as we need it to establish whether a cooperator exists.
	 */
	new_bfqq = bfq_find_close_cooperator(bfqd, bfqq,
			bfq_io_struct_pos(io_struct, request));

	if (new_bfqq && likely(new_bfqq != &bfqd->oom_bfqq) &&
	    bfq_may_be_close_cooperator(bfqq, new_bfqq))
		return bfq_setup_merge(bfqq, new_bfqq);

	return NULL;
}
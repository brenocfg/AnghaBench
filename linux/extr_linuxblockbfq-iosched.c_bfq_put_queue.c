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
struct bfq_queue {TYPE_1__* bfqd; scalar_t__ bic; int /*<<< orphan*/  burst_list_node; scalar_t__ ref; } ;
struct TYPE_2__ {scalar_t__ burst_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_log_bfqq (TYPE_1__*,struct bfq_queue*,char*,struct bfq_queue*,scalar_t__) ; 
 int /*<<< orphan*/  bfq_pool ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bfq_queue*) ; 

void bfq_put_queue(struct bfq_queue *bfqq)
{
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	struct bfq_group *bfqg = bfqq_group(bfqq);
#endif

	if (bfqq->bfqd)
		bfq_log_bfqq(bfqq->bfqd, bfqq, "put_queue: %p %d",
			     bfqq, bfqq->ref);

	bfqq->ref--;
	if (bfqq->ref)
		return;

	if (!hlist_unhashed(&bfqq->burst_list_node)) {
		hlist_del_init(&bfqq->burst_list_node);
		/*
		 * Decrement also burst size after the removal, if the
		 * process associated with bfqq is exiting, and thus
		 * does not contribute to the burst any longer. This
		 * decrement helps filter out false positives of large
		 * bursts, when some short-lived process (often due to
		 * the execution of commands by some service) happens
		 * to start and exit while a complex application is
		 * starting, and thus spawning several processes that
		 * do I/O (and that *must not* be treated as a large
		 * burst, see comments on bfq_handle_burst).
		 *
		 * In particular, the decrement is performed only if:
		 * 1) bfqq is not a merged queue, because, if it is,
		 * then this free of bfqq is not triggered by the exit
		 * of the process bfqq is associated with, but exactly
		 * by the fact that bfqq has just been merged.
		 * 2) burst_size is greater than 0, to handle
		 * unbalanced decrements. Unbalanced decrements may
		 * happen in te following case: bfqq is inserted into
		 * the current burst list--without incrementing
		 * bust_size--because of a split, but the current
		 * burst list is not the burst list bfqq belonged to
		 * (see comments on the case of a split in
		 * bfq_set_request).
		 */
		if (bfqq->bic && bfqq->bfqd->burst_size > 0)
			bfqq->bfqd->burst_size--;
	}

	kmem_cache_free(bfq_pool, bfqq);
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	bfqg_and_blkg_put(bfqg);
#endif
}
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
struct xpc_gru_mq_uv {unsigned long order; scalar_t__ address; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  kfree (struct xpc_gru_mq_uv*) ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xp_pa (scalar_t__) ; 
 int xp_restrict_memprotect (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xpc_gru_mq_watchlist_free_uv (struct xpc_gru_mq_uv*) ; 
 int /*<<< orphan*/  xpc_release_gru_mq_irq_uv (struct xpc_gru_mq_uv*) ; 

__attribute__((used)) static void
xpc_destroy_gru_mq_uv(struct xpc_gru_mq_uv *mq)
{
	unsigned int mq_size;
	int pg_order;
	int ret;

	/* disallow other partitions to access GRU mq */
	mq_size = 1UL << mq->order;
	ret = xp_restrict_memprotect(xp_pa(mq->address), mq_size);
	BUG_ON(ret != xpSuccess);

	/* unregister irq handler and release mq irq/vector mapping */
	free_irq(mq->irq, NULL);
	xpc_release_gru_mq_irq_uv(mq);

	/* disable generation of irq when GRU mq op occurs to this mq */
	xpc_gru_mq_watchlist_free_uv(mq);

	pg_order = mq->order - PAGE_SHIFT;
	free_pages((unsigned long)mq->address, pg_order);

	kfree(mq);
}
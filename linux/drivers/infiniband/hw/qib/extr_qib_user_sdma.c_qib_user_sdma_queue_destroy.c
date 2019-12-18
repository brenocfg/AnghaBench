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
struct qib_user_sdma_queue {scalar_t__ refcount; int /*<<< orphan*/  pkt_slab; int /*<<< orphan*/  header_cache; struct qib_user_sdma_queue* sdma_rb_node; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qib_user_sdma_queue*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_user_sdma_rb_root ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qib_user_sdma_queue_destroy(struct qib_user_sdma_queue *pq)
{
	if (!pq)
		return;

	pq->sdma_rb_node->refcount--;
	if (pq->sdma_rb_node->refcount == 0) {
		rb_erase(&pq->sdma_rb_node->node, &qib_user_sdma_rb_root);
		kfree(pq->sdma_rb_node);
	}
	dma_pool_destroy(pq->header_cache);
	kmem_cache_destroy(pq->pkt_slab);
	kfree(pq);
}
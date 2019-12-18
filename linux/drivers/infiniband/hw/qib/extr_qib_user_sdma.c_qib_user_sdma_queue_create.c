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
struct qib_user_sdma_rb_node {int refcount; int /*<<< orphan*/  pid; } ;
struct qib_user_sdma_queue {int /*<<< orphan*/  pkt_slab; int /*<<< orphan*/  header_cache; struct qib_user_sdma_rb_node* sdma_rb_node; int /*<<< orphan*/  dma_pages_root; int /*<<< orphan*/  header_cache_name; int /*<<< orphan*/  pkt_slab_name; int /*<<< orphan*/  lock; int /*<<< orphan*/  sent_lock; int /*<<< orphan*/  sent; scalar_t__ added; scalar_t__ num_sending; scalar_t__ num_pending; scalar_t__ sent_counter; scalar_t__ counter; } ;
struct qib_user_sdma_pkt {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QIB_USER_SDMA_EXP_HEADER_LENGTH ; 
 int /*<<< orphan*/  RB_ROOT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dma_pool_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qib_user_sdma_queue*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_user_sdma_rb_insert (int /*<<< orphan*/ *,struct qib_user_sdma_rb_node*) ; 
 int /*<<< orphan*/  qib_user_sdma_rb_root ; 
 struct qib_user_sdma_rb_node* qib_user_sdma_rb_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct qib_user_sdma_queue *
qib_user_sdma_queue_create(struct device *dev, int unit, int ctxt, int sctxt)
{
	struct qib_user_sdma_queue *pq =
		kmalloc(sizeof(struct qib_user_sdma_queue), GFP_KERNEL);
	struct qib_user_sdma_rb_node *sdma_rb_node;

	if (!pq)
		goto done;

	pq->counter = 0;
	pq->sent_counter = 0;
	pq->num_pending = 0;
	pq->num_sending = 0;
	pq->added = 0;
	pq->sdma_rb_node = NULL;

	INIT_LIST_HEAD(&pq->sent);
	spin_lock_init(&pq->sent_lock);
	mutex_init(&pq->lock);

	snprintf(pq->pkt_slab_name, sizeof(pq->pkt_slab_name),
		 "qib-user-sdma-pkts-%u-%02u.%02u", unit, ctxt, sctxt);
	pq->pkt_slab = kmem_cache_create(pq->pkt_slab_name,
					 sizeof(struct qib_user_sdma_pkt),
					 0, 0, NULL);

	if (!pq->pkt_slab)
		goto err_kfree;

	snprintf(pq->header_cache_name, sizeof(pq->header_cache_name),
		 "qib-user-sdma-headers-%u-%02u.%02u", unit, ctxt, sctxt);
	pq->header_cache = dma_pool_create(pq->header_cache_name,
					   dev,
					   QIB_USER_SDMA_EXP_HEADER_LENGTH,
					   4, 0);
	if (!pq->header_cache)
		goto err_slab;

	pq->dma_pages_root = RB_ROOT;

	sdma_rb_node = qib_user_sdma_rb_search(&qib_user_sdma_rb_root,
					current->pid);
	if (sdma_rb_node) {
		sdma_rb_node->refcount++;
	} else {
		sdma_rb_node = kmalloc(sizeof(
			struct qib_user_sdma_rb_node), GFP_KERNEL);
		if (!sdma_rb_node)
			goto err_rb;

		sdma_rb_node->refcount = 1;
		sdma_rb_node->pid = current->pid;

		qib_user_sdma_rb_insert(&qib_user_sdma_rb_root, sdma_rb_node);
	}
	pq->sdma_rb_node = sdma_rb_node;

	goto done;

err_rb:
	dma_pool_destroy(pq->header_cache);
err_slab:
	kmem_cache_destroy(pq->pkt_slab);
err_kfree:
	kfree(pq);
	pq = NULL;

done:
	return pq;
}
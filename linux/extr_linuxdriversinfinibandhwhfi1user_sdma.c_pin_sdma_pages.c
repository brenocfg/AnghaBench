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
struct user_sdma_request {struct hfi1_user_sdma_pkt_q* pq; } ;
struct TYPE_4__ {int /*<<< orphan*/  iov_len; scalar_t__ iov_base; } ;
struct user_sdma_iovec {TYPE_2__ iov; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct sdma_mmu_node {int npages; struct page** pages; TYPE_1__ rb; } ;
struct page {int dummy; } ;
struct hfi1_user_sdma_pkt_q {int /*<<< orphan*/  n_locked; int /*<<< orphan*/  mm; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int hfi1_acquire_user_pages (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  hfi1_can_pin_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct page** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  memcpy (struct page**,struct page**,int) ; 
 int sdma_cache_evict (struct hfi1_user_sdma_pkt_q*,int) ; 
 int /*<<< orphan*/  unpin_vector_pages (int /*<<< orphan*/ ,struct page**,int,int) ; 

__attribute__((used)) static int pin_sdma_pages(struct user_sdma_request *req,
			  struct user_sdma_iovec *iovec,
			  struct sdma_mmu_node *node,
			  int npages)
{
	int pinned, cleared;
	struct page **pages;
	struct hfi1_user_sdma_pkt_q *pq = req->pq;

	pages = kcalloc(npages, sizeof(*pages), GFP_KERNEL);
	if (!pages)
		return -ENOMEM;
	memcpy(pages, node->pages, node->npages * sizeof(*pages));

	npages -= node->npages;
retry:
	if (!hfi1_can_pin_pages(pq->dd, pq->mm,
				atomic_read(&pq->n_locked), npages)) {
		cleared = sdma_cache_evict(pq, npages);
		if (cleared >= npages)
			goto retry;
	}
	pinned = hfi1_acquire_user_pages(pq->mm,
					 ((unsigned long)iovec->iov.iov_base +
					 (node->npages * PAGE_SIZE)), npages, 0,
					 pages + node->npages);
	if (pinned < 0) {
		kfree(pages);
		return pinned;
	}
	if (pinned != npages) {
		unpin_vector_pages(pq->mm, pages, node->npages, pinned);
		return -EFAULT;
	}
	kfree(node->pages);
	node->rb.len = iovec->iov.iov_len;
	node->pages = pages;
	atomic_add(pinned, &pq->n_locked);
	return pinned;
}
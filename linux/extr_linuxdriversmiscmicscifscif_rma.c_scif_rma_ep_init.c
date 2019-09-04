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
struct scif_endpt_rma_info {int /*<<< orphan*/  markwq; int /*<<< orphan*/  vma_list; int /*<<< orphan*/  mmn_list; int /*<<< orphan*/ * dma_chan; scalar_t__ async_list_del; int /*<<< orphan*/  fence_refcount; int /*<<< orphan*/  tcw_total_pages; int /*<<< orphan*/  tcw_refcount; int /*<<< orphan*/  tw_refcount; int /*<<< orphan*/  remote_reg_list; int /*<<< orphan*/  reg_list; int /*<<< orphan*/  mmn_lock; int /*<<< orphan*/  tc_lock; int /*<<< orphan*/  iovad; int /*<<< orphan*/  rma_lock; } ;
struct scif_endpt {struct scif_endpt_rma_info rma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SCIF_IOVA_START_PFN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_iova_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void scif_rma_ep_init(struct scif_endpt *ep)
{
	struct scif_endpt_rma_info *rma = &ep->rma_info;

	mutex_init(&rma->rma_lock);
	init_iova_domain(&rma->iovad, PAGE_SIZE, SCIF_IOVA_START_PFN);
	spin_lock_init(&rma->tc_lock);
	mutex_init(&rma->mmn_lock);
	INIT_LIST_HEAD(&rma->reg_list);
	INIT_LIST_HEAD(&rma->remote_reg_list);
	atomic_set(&rma->tw_refcount, 0);
	atomic_set(&rma->tcw_refcount, 0);
	atomic_set(&rma->tcw_total_pages, 0);
	atomic_set(&rma->fence_refcount, 0);

	rma->async_list_del = 0;
	rma->dma_chan = NULL;
	INIT_LIST_HEAD(&rma->mmn_list);
	INIT_LIST_HEAD(&rma->vma_list);
	init_waitqueue_head(&rma->markwq);
}
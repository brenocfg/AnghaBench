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
struct t3_cqe {int dummy; } ;
struct t3_cq {unsigned long size_log2; int /*<<< orphan*/  cqid; int /*<<< orphan*/  queue; int /*<<< orphan*/  sw_queue; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct cxio_rdev {int /*<<< orphan*/  rscp; TYPE_2__ rnic_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxio_hal_clear_cq_ctx (struct cxio_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxio_hal_put_cqid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct t3_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 

void cxio_destroy_cq(struct cxio_rdev *rdev_p, struct t3_cq *cq)
{
	cxio_hal_clear_cq_ctx(rdev_p, cq->cqid);
	kfree(cq->sw_queue);
	dma_free_coherent(&(rdev_p->rnic_info.pdev->dev),
			  (1UL << (cq->size_log2))
			  * sizeof(struct t3_cqe) + 1, cq->queue,
			  dma_unmap_addr(cq, mapping));
	cxio_hal_put_cqid(rdev_p->rscp, cq->cqid);
}
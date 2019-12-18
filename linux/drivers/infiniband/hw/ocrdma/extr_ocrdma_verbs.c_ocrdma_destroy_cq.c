#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct ocrdma_eq {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  db_page_size; } ;
struct ocrdma_dev {TYPE_2__ nic_info; struct ocrdma_eq* eq_tbl; int /*<<< orphan*/ ** cq_tbl; } ;
struct ocrdma_cq {size_t id; TYPE_3__* ucontext; int /*<<< orphan*/  len; scalar_t__ pa; int /*<<< orphan*/  eqn; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__* cntxt_pd; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 struct ocrdma_cq* get_ocrdma_cq (struct ib_cq*) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_flush_cq (struct ocrdma_cq*) ; 
 int /*<<< orphan*/  ocrdma_get_db_addr (struct ocrdma_dev*,int) ; 
 size_t ocrdma_get_eq_table_index (struct ocrdma_dev*,int /*<<< orphan*/ ) ; 
 size_t ocrdma_get_irq (struct ocrdma_dev*,struct ocrdma_eq*) ; 
 int /*<<< orphan*/  ocrdma_mbx_destroy_cq (struct ocrdma_dev*,struct ocrdma_cq*) ; 
 int /*<<< orphan*/  synchronize_irq (size_t) ; 

void ocrdma_destroy_cq(struct ib_cq *ibcq, struct ib_udata *udata)
{
	struct ocrdma_cq *cq = get_ocrdma_cq(ibcq);
	struct ocrdma_eq *eq = NULL;
	struct ocrdma_dev *dev = get_ocrdma_dev(ibcq->device);
	int pdid = 0;
	u32 irq, indx;

	dev->cq_tbl[cq->id] = NULL;
	indx = ocrdma_get_eq_table_index(dev, cq->eqn);

	eq = &dev->eq_tbl[indx];
	irq = ocrdma_get_irq(dev, eq);
	synchronize_irq(irq);
	ocrdma_flush_cq(cq);

	ocrdma_mbx_destroy_cq(dev, cq);
	if (cq->ucontext) {
		pdid = cq->ucontext->cntxt_pd->id;
		ocrdma_del_mmap(cq->ucontext, (u64) cq->pa,
				PAGE_ALIGN(cq->len));
		ocrdma_del_mmap(cq->ucontext,
				ocrdma_get_db_addr(dev, pdid),
				dev->nic_info.db_page_size);
	}
}
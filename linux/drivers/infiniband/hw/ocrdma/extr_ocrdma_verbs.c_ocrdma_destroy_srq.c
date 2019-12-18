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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  len; scalar_t__ pa; } ;
struct ocrdma_srq {int /*<<< orphan*/  rqe_wr_id_tbl; int /*<<< orphan*/  idx_bit_fields; TYPE_2__ rq; TYPE_1__* pd; } ;
struct ocrdma_dev {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {scalar_t__ uctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_srq* get_ocrdma_srq (struct ib_srq*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_mbx_destroy_srq (struct ocrdma_dev*,struct ocrdma_srq*) ; 

void ocrdma_destroy_srq(struct ib_srq *ibsrq, struct ib_udata *udata)
{
	struct ocrdma_srq *srq;
	struct ocrdma_dev *dev = get_ocrdma_dev(ibsrq->device);

	srq = get_ocrdma_srq(ibsrq);

	ocrdma_mbx_destroy_srq(dev, srq);

	if (srq->pd->uctx)
		ocrdma_del_mmap(srq->pd->uctx, (u64) srq->rq.pa,
				PAGE_ALIGN(srq->rq.len));

	kfree(srq->idx_bit_fields);
	kfree(srq->rqe_wr_id_tbl);
}
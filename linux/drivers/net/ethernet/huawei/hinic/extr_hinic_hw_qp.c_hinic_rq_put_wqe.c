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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct hinic_rq_cqe {int /*<<< orphan*/  status; } ;
struct hinic_rq {int /*<<< orphan*/  wq; struct hinic_rq_cqe** cqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_RQ_CQE_STATUS_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXDONE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_put_wqe (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

void hinic_rq_put_wqe(struct hinic_rq *rq, u16 cons_idx,
		      unsigned int wqe_size)
{
	struct hinic_rq_cqe *cqe = rq->cqe[cons_idx];
	u32 status = be32_to_cpu(cqe->status);

	status = HINIC_RQ_CQE_STATUS_CLEAR(status, RXDONE);

	/* Rx WQE size is 1 WQEBB, no wq shadow*/
	cqe->status = cpu_to_be32(status);

	wmb();          /* clear done flag */

	hinic_put_wqe(rq->wq, wqe_size);
}
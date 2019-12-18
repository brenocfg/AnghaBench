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
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  in_use; int /*<<< orphan*/  rqt_size; int /*<<< orphan*/  rqt_hwaddr; int /*<<< orphan*/  msn; int /*<<< orphan*/  wq_pidx; int /*<<< orphan*/  pidx; int /*<<< orphan*/  cidx; int /*<<< orphan*/  memsize; int /*<<< orphan*/  qid; } ;
struct t4_wq {TYPE_1__ rq; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ rdma_nl_put_driver_u32 (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u32_hex (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_rq(struct sk_buff *msg, struct t4_wq *wq)
{
	/* RQ */
	if (rdma_nl_put_driver_u32(msg, "rqid", wq->rq.qid))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "memsize", wq->rq.memsize))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "cidx", wq->rq.cidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "pidx", wq->rq.pidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "wq_pidx", wq->rq.wq_pidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "msn", wq->rq.msn))
		goto err;
	if (rdma_nl_put_driver_u32_hex(msg, "rqt_hwaddr", wq->rq.rqt_hwaddr))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "rqt_size", wq->rq.rqt_size))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "in_use", wq->rq.in_use))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "size", wq->rq.size))
		goto err;
	return 0;
err:
	return -EMSGSIZE;
}
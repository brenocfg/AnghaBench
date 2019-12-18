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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  in_use; int /*<<< orphan*/  flush_cidx; int /*<<< orphan*/  wq_pidx; int /*<<< orphan*/  pidx; int /*<<< orphan*/  cidx; int /*<<< orphan*/  memsize; int /*<<< orphan*/  qid; } ;
struct t4_wq {TYPE_1__ sq; int /*<<< orphan*/  flushed; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ rdma_nl_put_driver_u32 (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u32_hex (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_sq(struct sk_buff *msg, struct t4_wq *wq)
{
	/* WQ+SQ */
	if (rdma_nl_put_driver_u32(msg, "sqid", wq->sq.qid))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "flushed", wq->flushed))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "memsize", wq->sq.memsize))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "cidx", wq->sq.cidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "pidx", wq->sq.pidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "wq_pidx", wq->sq.wq_pidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "flush_cidx", wq->sq.flush_cidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "in_use", wq->sq.in_use))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "size", wq->sq.size))
		goto err;
	if (rdma_nl_put_driver_u32_hex(msg, "flags", wq->sq.flags))
		goto err;
	return 0;
err:
	return -EMSGSIZE;
}
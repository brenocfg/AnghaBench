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
struct t4_cq {int /*<<< orphan*/  flags; int /*<<< orphan*/  bits_type_ts; int /*<<< orphan*/  error; int /*<<< orphan*/  gen; int /*<<< orphan*/  vector; int /*<<< orphan*/  sw_in_use; int /*<<< orphan*/  sw_pidx; int /*<<< orphan*/  sw_cidx; int /*<<< orphan*/  cidx_inc; int /*<<< orphan*/  cidx; int /*<<< orphan*/  size; int /*<<< orphan*/  memsize; int /*<<< orphan*/  cqid; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u32 (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_nl_put_driver_u64_hex (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_cq(struct sk_buff *msg, struct t4_cq *cq)
{
	if (rdma_nl_put_driver_u32(msg, "cqid", cq->cqid))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "memsize", cq->memsize))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "size", cq->size))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "cidx", cq->cidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "cidx_inc", cq->cidx_inc))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "sw_cidx", cq->sw_cidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "sw_pidx", cq->sw_pidx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "sw_in_use", cq->sw_in_use))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "vector", cq->vector))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "gen", cq->gen))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "error", cq->error))
		goto err;
	if (rdma_nl_put_driver_u64_hex(msg, "bits_type_ts",
					 be64_to_cpu(cq->bits_type_ts)))
		goto err;
	if (rdma_nl_put_driver_u64_hex(msg, "flags", cq->flags))
		goto err;

	return 0;

err:
	return -EMSGSIZE;
}
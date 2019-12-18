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
typedef  scalar_t__ u16 ;
struct t4_swsqe {scalar_t__ flushed; scalar_t__ signaled; int /*<<< orphan*/  cqe; scalar_t__ complete; scalar_t__ opcode; } ;
struct t4_sq {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ CQE_STATUS (int /*<<< orphan*/ *) ; 
 int EMSGSIZE ; 
 scalar_t__ rdma_nl_put_driver_u32 (struct sk_buff*,char*,scalar_t__) ; 

__attribute__((used)) static int fill_swsqe(struct sk_buff *msg, struct t4_sq *sq, u16 idx,
		      struct t4_swsqe *sqe)
{
	if (rdma_nl_put_driver_u32(msg, "idx", idx))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "opcode", sqe->opcode))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "complete", sqe->complete))
		goto err;
	if (sqe->complete &&
	    rdma_nl_put_driver_u32(msg, "cqe_status", CQE_STATUS(&sqe->cqe)))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "signaled", sqe->signaled))
		goto err;
	if (rdma_nl_put_driver_u32(msg, "flushed", sqe->flushed))
		goto err;
	return 0;
err:
	return -EMSGSIZE;
}
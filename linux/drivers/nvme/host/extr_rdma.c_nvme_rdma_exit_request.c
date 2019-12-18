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
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nvme_rdma_request {TYPE_1__ sqe; } ;
struct blk_mq_tag_set {int dummy; } ;

/* Variables and functions */
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_rdma_exit_request(struct blk_mq_tag_set *set,
		struct request *rq, unsigned int hctx_idx)
{
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);

	kfree(req->sqe.data);
}
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
struct blk_mq_tag_set {struct nvme_loop_ctrl* driver_data; } ;
struct nvme_loop_ctrl {struct blk_mq_tag_set tag_set; int /*<<< orphan*/  ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_rq_to_pdu (struct request*) ; 
 int nvme_loop_init_iod (struct nvme_loop_ctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* nvme_req (struct request*) ; 

__attribute__((used)) static int nvme_loop_init_request(struct blk_mq_tag_set *set,
		struct request *req, unsigned int hctx_idx,
		unsigned int numa_node)
{
	struct nvme_loop_ctrl *ctrl = set->driver_data;

	nvme_req(req)->ctrl = &ctrl->ctrl;
	return nvme_loop_init_iod(ctrl, blk_mq_rq_to_pdu(req),
			(set == &ctrl->tag_set) ? hctx_idx + 1 : 0);
}
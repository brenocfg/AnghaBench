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
struct TYPE_4__ {int /*<<< orphan*/  ddcb_prev; int /*<<< orphan*/  ddcb_finished; } ;
struct TYPE_3__ {void* retc; int /*<<< orphan*/  progress; void* attn; void* cmplt_ts; void* deque_ts; void* vcrc; int /*<<< orphan*/ * asv; } ;
struct ddcb_requ {size_t num; TYPE_2__ debug_data; TYPE_1__ cmd; struct ddcb_queue* queue; } ;
struct ddcb_queue {int ddcb_max; struct ddcb* ddcb_vaddr; } ;
struct ddcb {int /*<<< orphan*/  retc_16; int /*<<< orphan*/  progress_32; int /*<<< orphan*/  attn_16; int /*<<< orphan*/  cmplt_ts_64; int /*<<< orphan*/  deque_ts_64; int /*<<< orphan*/  vcrc_16; struct ddcb* asv; } ;

/* Variables and functions */
 int DDCB_ASV_LENGTH ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ddcb_requ_collect_debug_data (struct ddcb_requ*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ddcb*,int) ; 

__attribute__((used)) static void copy_ddcb_results(struct ddcb_requ *req, int ddcb_no)
{
	struct ddcb_queue *queue = req->queue;
	struct ddcb *pddcb = &queue->ddcb_vaddr[req->num];

	memcpy(&req->cmd.asv[0], &pddcb->asv[0], DDCB_ASV_LENGTH);

	/* copy status flags of the variant part */
	req->cmd.vcrc     = be16_to_cpu(pddcb->vcrc_16);
	req->cmd.deque_ts = be64_to_cpu(pddcb->deque_ts_64);
	req->cmd.cmplt_ts = be64_to_cpu(pddcb->cmplt_ts_64);

	req->cmd.attn     = be16_to_cpu(pddcb->attn_16);
	req->cmd.progress = be32_to_cpu(pddcb->progress_32);
	req->cmd.retc     = be16_to_cpu(pddcb->retc_16);

	if (ddcb_requ_collect_debug_data(req)) {
		int prev_no = (ddcb_no == 0) ?
			queue->ddcb_max - 1 : ddcb_no - 1;
		struct ddcb *prev_pddcb = &queue->ddcb_vaddr[prev_no];

		memcpy(&req->debug_data.ddcb_finished, pddcb,
		       sizeof(req->debug_data.ddcb_finished));
		memcpy(&req->debug_data.ddcb_prev, prev_pddcb,
		       sizeof(req->debug_data.ddcb_prev));
	}
}
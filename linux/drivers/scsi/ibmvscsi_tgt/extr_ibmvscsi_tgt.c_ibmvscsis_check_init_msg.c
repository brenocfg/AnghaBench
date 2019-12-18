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
typedef  scalar_t__ uint ;
struct viosrp_crq {scalar_t__ valid; scalar_t__ format; } ;
struct TYPE_2__ {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  index; int /*<<< orphan*/  mask; } ;
struct scsi_info {TYPE_1__ cmd_q; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 long ERROR ; 
 scalar_t__ INIT_MSG ; 
 void* INVALIDATE_CMD_RESP_EL ; 
 scalar_t__ UNUSED_FORMAT ; 
 scalar_t__ VALID_INIT_MSG ; 
 int /*<<< orphan*/  dma_rmb () ; 
 struct viosrp_crq* ibmvscsis_cmd_q_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_check_init_msg(struct scsi_info *vscsi, uint *format)
{
	struct viosrp_crq *crq;
	long rc = ADAPT_SUCCESS;

	crq = ibmvscsis_cmd_q_dequeue(vscsi->cmd_q.mask, &vscsi->cmd_q.index,
				      vscsi->cmd_q.base_addr);
	if (!crq) {
		*format = (uint)UNUSED_FORMAT;
	} else if (crq->valid == VALID_INIT_MSG && crq->format == INIT_MSG) {
		*format = (uint)INIT_MSG;
		crq->valid = INVALIDATE_CMD_RESP_EL;
		dma_rmb();

		/*
		 * the caller has ensured no initialize message was
		 * sent after the queue was
		 * created so there should be no other message on the queue.
		 */
		crq = ibmvscsis_cmd_q_dequeue(vscsi->cmd_q.mask,
					      &vscsi->cmd_q.index,
					      vscsi->cmd_q.base_addr);
		if (crq) {
			*format = (uint)(crq->format);
			rc = ERROR;
			crq->valid = INVALIDATE_CMD_RESP_EL;
			dma_rmb();
		}
	} else {
		*format = (uint)(crq->format);
		rc = ERROR;
		crq->valid = INVALIDATE_CMD_RESP_EL;
		dma_rmb();
	}

	return rc;
}
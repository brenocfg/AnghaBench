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
struct TYPE_4__ {int size; int /*<<< orphan*/  crq_token; } ;
struct TYPE_3__ {int /*<<< orphan*/  unit_id; } ;
struct scsi_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; TYPE_2__ cmd_q; TYPE_1__ dds; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 int /*<<< orphan*/  ERR_DISCONNECTED ; 
 long H_CLOSED ; 
 long H_SUCCESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RESPONSE_Q_DOWN ; 
 int /*<<< orphan*/  WAIT_CONNECTION ; 
 long h_reg_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 long ibmvscsis_establish_new_q (struct scsi_info*) ; 

__attribute__((used)) static long ibmvscsis_enable_change_state(struct scsi_info *vscsi)
{
	int bytes;
	long rc = ADAPT_SUCCESS;

	bytes = vscsi->cmd_q.size * PAGE_SIZE;
	rc = h_reg_crq(vscsi->dds.unit_id, vscsi->cmd_q.crq_token, bytes);
	if (rc == H_CLOSED || rc == H_SUCCESS) {
		vscsi->state = WAIT_CONNECTION;
		rc = ibmvscsis_establish_new_q(vscsi);
	}

	if (rc != ADAPT_SUCCESS) {
		vscsi->state = ERR_DISCONNECTED;
		vscsi->flags |= RESPONSE_Q_DOWN;
	}

	return rc;
}
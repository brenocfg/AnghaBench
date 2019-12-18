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
struct ims_pcu {int* read_buf; int expected_response; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  read_pos; int /*<<< orphan*/  cmd_buf_len; int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/  ack_id; int /*<<< orphan*/  setup_complete; } ;

/* Variables and functions */
#define  IMS_PCU_RSP_EVNT_BUTTONS 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ims_pcu_report_events (struct ims_pcu*) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ims_pcu_handle_response(struct ims_pcu *pcu)
{
	switch (pcu->read_buf[0]) {
	case IMS_PCU_RSP_EVNT_BUTTONS:
		if (likely(pcu->setup_complete))
			ims_pcu_report_events(pcu);
		break;

	default:
		/*
		 * See if we got command completion.
		 * If both the sequence and response code match save
		 * the data and signal completion.
		 */
		if (pcu->read_buf[0] == pcu->expected_response &&
		    pcu->read_buf[1] == pcu->ack_id - 1) {

			memcpy(pcu->cmd_buf, pcu->read_buf, pcu->read_pos);
			pcu->cmd_buf_len = pcu->read_pos;
			complete(&pcu->cmd_done);
		}
		break;
	}
}
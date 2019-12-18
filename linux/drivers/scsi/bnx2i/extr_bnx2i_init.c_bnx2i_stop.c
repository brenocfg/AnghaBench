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
struct bnx2i_hba {int hba_shutdown_tmo; int ofld_conns_active; int /*<<< orphan*/  adapter_state; int /*<<< orphan*/  eh_wait; int /*<<< orphan*/  ep_destroy_list; int /*<<< orphan*/  ep_ofld_list; int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_GOING_DOWN ; 
 int /*<<< orphan*/  ADAPTER_STATE_UP ; 
 int HZ ; 
 int /*<<< orphan*/  bnx2i_chip_cleanup (struct bnx2i_hba*) ; 
 int /*<<< orphan*/  bnx2i_drop_session ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_host_for_each_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

void bnx2i_stop(void *handle)
{
	struct bnx2i_hba *hba = handle;
	int conns_active;
	int wait_delay = 1 * HZ;

	/* check if cleanup happened in GOING_DOWN context */
	if (!test_and_set_bit(ADAPTER_STATE_GOING_DOWN,
			      &hba->adapter_state)) {
		iscsi_host_for_each_session(hba->shost,
					    bnx2i_drop_session);
		wait_delay = hba->hba_shutdown_tmo;
	}
	/* Wait for inflight offload connection tasks to complete before
	 * proceeding. Forcefully terminate all connection recovery in
	 * progress at the earliest, either in bind(), send_pdu(LOGIN),
	 * or conn_start()
	 */
	wait_event_interruptible_timeout(hba->eh_wait,
					 (list_empty(&hba->ep_ofld_list) &&
					 list_empty(&hba->ep_destroy_list)),
					 2 * HZ);
	/* Wait for all endpoints to be torn down, Chip will be reset once
	 *  control returns to network driver. So it is required to cleanup and
	 * release all connection resources before returning from this routine.
	 */
	while (hba->ofld_conns_active) {
		conns_active = hba->ofld_conns_active;
		wait_event_interruptible_timeout(hba->eh_wait,
				(hba->ofld_conns_active != conns_active),
				wait_delay);
		if (hba->ofld_conns_active == conns_active)
			break;
	}
	bnx2i_chip_cleanup(hba);

	/* This flag should be cleared last so that ep_disconnect() gracefully
	 * cleans up connection context
	 */
	clear_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
	clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
}
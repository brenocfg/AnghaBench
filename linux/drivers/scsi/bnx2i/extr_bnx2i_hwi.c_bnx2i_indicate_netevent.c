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
struct bnx2i_hba {int /*<<< orphan*/  shost; int /*<<< orphan*/  adapter_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_GOING_DOWN ; 
 int /*<<< orphan*/  ADAPTER_STATE_UP ; 
#define  NETDEV_CHANGE 131 
#define  NETDEV_DOWN 130 
#define  NETDEV_GOING_DOWN 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  bnx2i_drop_session ; 
 int /*<<< orphan*/  bnx2i_get_link_state (struct bnx2i_hba*) ; 
 int /*<<< orphan*/  bnx2i_send_fw_iscsi_init_msg (struct bnx2i_hba*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_host_for_each_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_indicate_netevent(void *context, unsigned long event,
				    u16 vlan_id)
{
	struct bnx2i_hba *hba = context;

	/* Ignore all netevent coming from vlans */
	if (vlan_id != 0)
		return;

	switch (event) {
	case NETDEV_UP:
		if (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state))
			bnx2i_send_fw_iscsi_init_msg(hba);
		break;
	case NETDEV_DOWN:
		clear_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
		clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
		break;
	case NETDEV_GOING_DOWN:
		set_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
		iscsi_host_for_each_session(hba->shost,
					    bnx2i_drop_session);
		break;
	case NETDEV_CHANGE:
		bnx2i_get_link_state(hba);
		break;
	default:
		;
	}
}
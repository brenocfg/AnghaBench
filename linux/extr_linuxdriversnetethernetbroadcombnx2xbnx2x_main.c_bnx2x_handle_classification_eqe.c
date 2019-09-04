#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  echo; } ;
struct TYPE_6__ {TYPE_1__ eth_event; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
union event_ring_elem {TYPE_3__ message; } ;
typedef  int u32 ;
struct bnx2x_vlan_mac_obj {int (* complete ) (struct bnx2x*,struct bnx2x_vlan_mac_obj*,union event_ring_elem*,unsigned long*) ;} ;
struct bnx2x {TYPE_4__* sp_objs; struct bnx2x_vlan_mac_obj iscsi_l2_mac_obj; } ;
struct TYPE_8__ {struct bnx2x_vlan_mac_obj vlan_obj; struct bnx2x_vlan_mac_obj mac_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_FILTER_MAC_PENDING 130 
#define  BNX2X_FILTER_MCAST_PENDING 129 
#define  BNX2X_FILTER_VLAN_PENDING 128 
 int BNX2X_ISCSI_ETH_CID (struct bnx2x*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BNX2X_SWCID_MASK ; 
 int BNX2X_SWCID_SHIFT ; 
 int /*<<< orphan*/  CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  bnx2x_handle_mcast_eqe (struct bnx2x*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,union event_ring_elem*,unsigned long*) ; 

__attribute__((used)) static void bnx2x_handle_classification_eqe(struct bnx2x *bp,
					    union event_ring_elem *elem)
{
	unsigned long ramrod_flags = 0;
	int rc = 0;
	u32 echo = le32_to_cpu(elem->message.data.eth_event.echo);
	u32 cid = echo & BNX2X_SWCID_MASK;
	struct bnx2x_vlan_mac_obj *vlan_mac_obj;

	/* Always push next commands out, don't wait here */
	__set_bit(RAMROD_CONT, &ramrod_flags);

	switch (echo >> BNX2X_SWCID_SHIFT) {
	case BNX2X_FILTER_MAC_PENDING:
		DP(BNX2X_MSG_SP, "Got SETUP_MAC completions\n");
		if (CNIC_LOADED(bp) && (cid == BNX2X_ISCSI_ETH_CID(bp)))
			vlan_mac_obj = &bp->iscsi_l2_mac_obj;
		else
			vlan_mac_obj = &bp->sp_objs[cid].mac_obj;

		break;
	case BNX2X_FILTER_VLAN_PENDING:
		DP(BNX2X_MSG_SP, "Got SETUP_VLAN completions\n");
		vlan_mac_obj = &bp->sp_objs[cid].vlan_obj;
		break;
	case BNX2X_FILTER_MCAST_PENDING:
		DP(BNX2X_MSG_SP, "Got SETUP_MCAST completions\n");
		/* This is only relevant for 57710 where multicast MACs are
		 * configured as unicast MACs using the same ramrod.
		 */
		bnx2x_handle_mcast_eqe(bp);
		return;
	default:
		BNX2X_ERR("Unsupported classification command: 0x%x\n", echo);
		return;
	}

	rc = vlan_mac_obj->complete(bp, vlan_mac_obj, elem, &ramrod_flags);

	if (rc < 0)
		BNX2X_ERR("Failed to schedule new commands: %d\n", rc);
	else if (rc > 0)
		DP(BNX2X_MSG_SP, "Scheduled next pending commands...\n");
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* inner_mac; int /*<<< orphan*/  mac_lsb; int /*<<< orphan*/  mac_mid; int /*<<< orphan*/  mac_msb; int /*<<< orphan*/  header; } ;
union eth_classify_rule_cmd {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  u8 ;
struct eth_classify_rules_ramrod_data {int /*<<< orphan*/  header; union eth_classify_rule_cmd* rules; } ;
struct bnx2x_raw_obj {int /*<<< orphan*/  state; int /*<<< orphan*/  cid; int /*<<< orphan*/  cl_id; scalar_t__ rdata; } ;
struct bnx2x_vlan_mac_obj {struct bnx2x_raw_obj raw; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_inner_mac; int /*<<< orphan*/ * mac; } ;
struct TYPE_8__ {TYPE_2__ mac; } ;
struct TYPE_9__ {int cmd; unsigned long vlan_mac_flags; TYPE_3__ u; struct bnx2x_vlan_mac_obj* target_obj; } ;
struct TYPE_10__ {TYPE_4__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_5__ cmd_data; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ETH_MAC ; 
 int /*<<< orphan*/  BNX2X_ISCSI_ETH_MAC ; 
 int /*<<< orphan*/  BNX2X_LLH_CAM_ETH_LINE ; 
 int /*<<< orphan*/  BNX2X_LLH_CAM_ISCSI_ETH_LINE ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BNX2X_VLAN_MAC_ADD ; 
 int BNX2X_VLAN_MAC_MOVE ; 
 int /*<<< orphan*/  CLASSIFY_RULE_OPCODE_MAC ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_fw_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_set_mac_in_nig (struct bnx2x*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vlan_mac_set_cmd_hdr_e2 (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_vlan_mac_set_rdata_hdr_e2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct eth_classify_rules_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void bnx2x_set_one_mac_e2(struct bnx2x *bp,
				 struct bnx2x_vlan_mac_obj *o,
				 struct bnx2x_exeq_elem *elem, int rule_idx,
				 int cam_offset)
{
	struct bnx2x_raw_obj *raw = &o->raw;
	struct eth_classify_rules_ramrod_data *data =
		(struct eth_classify_rules_ramrod_data *)(raw->rdata);
	int rule_cnt = rule_idx + 1, cmd = elem->cmd_data.vlan_mac.cmd;
	union eth_classify_rule_cmd *rule_entry = &data->rules[rule_idx];
	bool add = (cmd == BNX2X_VLAN_MAC_ADD) ? true : false;
	unsigned long *vlan_mac_flags = &elem->cmd_data.vlan_mac.vlan_mac_flags;
	u8 *mac = elem->cmd_data.vlan_mac.u.mac.mac;

	/* Set LLH CAM entry: currently only iSCSI and ETH macs are
	 * relevant. In addition, current implementation is tuned for a
	 * single ETH MAC.
	 *
	 * When multiple unicast ETH MACs PF configuration in switch
	 * independent mode is required (NetQ, multiple netdev MACs,
	 * etc.), consider better utilisation of 8 per function MAC
	 * entries in the LLH register. There is also
	 * NIG_REG_P[01]_LLH_FUNC_MEM2 registers that complete the
	 * total number of CAM entries to 16.
	 *
	 * Currently we won't configure NIG for MACs other than a primary ETH
	 * MAC and iSCSI L2 MAC.
	 *
	 * If this MAC is moving from one Queue to another, no need to change
	 * NIG configuration.
	 */
	if (cmd != BNX2X_VLAN_MAC_MOVE) {
		if (test_bit(BNX2X_ISCSI_ETH_MAC, vlan_mac_flags))
			bnx2x_set_mac_in_nig(bp, add, mac,
					     BNX2X_LLH_CAM_ISCSI_ETH_LINE);
		else if (test_bit(BNX2X_ETH_MAC, vlan_mac_flags))
			bnx2x_set_mac_in_nig(bp, add, mac,
					     BNX2X_LLH_CAM_ETH_LINE);
	}

	/* Reset the ramrod data buffer for the first rule */
	if (rule_idx == 0)
		memset(data, 0, sizeof(*data));

	/* Setup a command header */
	bnx2x_vlan_mac_set_cmd_hdr_e2(bp, o, add, CLASSIFY_RULE_OPCODE_MAC,
				      &rule_entry->mac.header);

	DP(BNX2X_MSG_SP, "About to %s MAC %pM for Queue %d\n",
	   (add ? "add" : "delete"), mac, raw->cl_id);

	/* Set a MAC itself */
	bnx2x_set_fw_mac_addr(&rule_entry->mac.mac_msb,
			      &rule_entry->mac.mac_mid,
			      &rule_entry->mac.mac_lsb, mac);
	rule_entry->mac.inner_mac =
		cpu_to_le16(elem->cmd_data.vlan_mac.u.mac.is_inner_mac);

	/* MOVE: Add a rule that will add this MAC to the target Queue */
	if (cmd == BNX2X_VLAN_MAC_MOVE) {
		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		bnx2x_vlan_mac_set_cmd_hdr_e2(bp,
					elem->cmd_data.vlan_mac.target_obj,
					      true, CLASSIFY_RULE_OPCODE_MAC,
					      &rule_entry->mac.header);

		/* Set a MAC itself */
		bnx2x_set_fw_mac_addr(&rule_entry->mac.mac_msb,
				      &rule_entry->mac.mac_mid,
				      &rule_entry->mac.mac_lsb, mac);
		rule_entry->mac.inner_mac =
			cpu_to_le16(elem->cmd_data.vlan_mac.
						u.mac.is_inner_mac);
	}

	/* Set the ramrod data header */
	/* TODO: take this to the higher level in order to prevent multiple
		 writing */
	bnx2x_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
}
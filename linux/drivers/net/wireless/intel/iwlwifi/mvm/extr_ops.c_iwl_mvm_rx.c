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
typedef  int /*<<< orphan*/  u16 ;
struct napi_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  group_id; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  LEGACY_GROUP ; 
 int /*<<< orphan*/  REPLY_RX_MPDU_CMD ; 
 int /*<<< orphan*/  REPLY_RX_PHY_CMD ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_rx_common (struct iwl_mvm*,struct iwl_rx_cmd_buffer*,struct iwl_rx_packet*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_rx_mpdu (struct iwl_mvm*,struct napi_struct*,struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_rx_phy_cmd (struct iwl_mvm*,struct iwl_rx_cmd_buffer*) ; 
 scalar_t__ likely (int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static void iwl_mvm_rx(struct iwl_op_mode *op_mode,
		       struct napi_struct *napi,
		       struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	u16 cmd = WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd);

	if (likely(cmd == WIDE_ID(LEGACY_GROUP, REPLY_RX_MPDU_CMD)))
		iwl_mvm_rx_rx_mpdu(mvm, napi, rxb);
	else if (cmd == WIDE_ID(LEGACY_GROUP, REPLY_RX_PHY_CMD))
		iwl_mvm_rx_rx_phy_cmd(mvm, rxb);
	else
		iwl_mvm_rx_common(mvm, rxb, pkt);
}
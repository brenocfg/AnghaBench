#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  token_cmd ;
struct TYPE_4__ {int /*<<< orphan*/  lan_id; } ;
struct ixgbe_hw {TYPE_1__ bus; } ;
struct TYPE_5__ {scalar_t__ ret_status; scalar_t__ cmd_resv; } ;
struct TYPE_6__ {TYPE_2__ cmd_or_resp; int /*<<< orphan*/  checksum; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  cmd; } ;
struct ixgbe_hic_phy_token_req {TYPE_3__ hdr; scalar_t__ pad; int /*<<< orphan*/  command_type; int /*<<< orphan*/  port_number; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT_CHECKSUM ; 
 scalar_t__ FW_PHY_TOKEN_OK ; 
 int /*<<< orphan*/  FW_PHY_TOKEN_REQ ; 
 int /*<<< orphan*/  FW_PHY_TOKEN_REQ_CMD ; 
 int /*<<< orphan*/  FW_PHY_TOKEN_REQ_LEN ; 
 scalar_t__ FW_PHY_TOKEN_RETRY ; 
 scalar_t__ IXGBE_ERR_FW_RESP_INVALID ; 
 scalar_t__ IXGBE_ERR_TOKEN_RETRY ; 
 int /*<<< orphan*/  IXGBE_HI_COMMAND_TIMEOUT ; 
 scalar_t__ ixgbe_host_interface_command (struct ixgbe_hw*,struct ixgbe_hic_phy_token_req*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_get_phy_token(struct ixgbe_hw *hw)
{
	struct ixgbe_hic_phy_token_req token_cmd;
	s32 status;

	token_cmd.hdr.cmd = FW_PHY_TOKEN_REQ_CMD;
	token_cmd.hdr.buf_len = FW_PHY_TOKEN_REQ_LEN;
	token_cmd.hdr.cmd_or_resp.cmd_resv = 0;
	token_cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
	token_cmd.port_number = hw->bus.lan_id;
	token_cmd.command_type = FW_PHY_TOKEN_REQ;
	token_cmd.pad = 0;
	status = ixgbe_host_interface_command(hw, &token_cmd, sizeof(token_cmd),
					      IXGBE_HI_COMMAND_TIMEOUT,
					      true);
	if (status)
		return status;
	if (token_cmd.hdr.cmd_or_resp.ret_status == FW_PHY_TOKEN_OK)
		return 0;
	if (token_cmd.hdr.cmd_or_resp.ret_status != FW_PHY_TOKEN_RETRY)
		return IXGBE_ERR_FW_RESP_INVALID;

	return IXGBE_ERR_TOKEN_RETRY;
}
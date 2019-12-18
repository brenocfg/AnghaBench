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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_phy_context_cmd {void* apply_time; void* action; void* id_and_color; } ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_phy_context_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_phy_ctxt_cmd_hdr(struct iwl_mvm_phy_ctxt *ctxt,
				     struct iwl_phy_context_cmd *cmd,
				     u32 action, u32 apply_time)
{
	memset(cmd, 0, sizeof(struct iwl_phy_context_cmd));

	cmd->id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(ctxt->id,
							    ctxt->color));
	cmd->action = cpu_to_le32(action);
	cmd->apply_time = cpu_to_le32(apply_time);
}
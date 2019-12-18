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
struct iwl_mvm {int dummy; } ;
struct iwl_lq_cmd {scalar_t__ sta_id; } ;
struct iwl_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int EINVAL ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  LQ_CMD ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ iwl_mvm_has_tlc_offload (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 

int iwl_mvm_send_lq_cmd(struct iwl_mvm *mvm, struct iwl_lq_cmd *lq)
{
	struct iwl_host_cmd cmd = {
		.id = LQ_CMD,
		.len = { sizeof(struct iwl_lq_cmd), },
		.flags = CMD_ASYNC,
		.data = { lq, },
	};

	if (WARN_ON(lq->sta_id == IWL_MVM_INVALID_STA ||
		    iwl_mvm_has_tlc_offload(mvm)))
		return -EINVAL;

	return iwl_mvm_send_cmd(mvm, &cmd);
}
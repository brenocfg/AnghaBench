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
struct iwl_wowlan_status {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  OFFLOADS_QUERY_CMD ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iwl_wowlan_status* iwl_mvm_send_wowlan_get_status (struct iwl_mvm*) ; 

__attribute__((used)) static struct iwl_wowlan_status *
iwl_mvm_get_wakeup_status(struct iwl_mvm *mvm)
{
	int ret;

	/* only for tracing for now */
	ret = iwl_mvm_send_cmd_pdu(mvm, OFFLOADS_QUERY_CMD, 0, 0, NULL);
	if (ret)
		IWL_ERR(mvm, "failed to query offload statistics (%d)\n", ret);

	return iwl_mvm_send_wowlan_get_status(mvm);
}
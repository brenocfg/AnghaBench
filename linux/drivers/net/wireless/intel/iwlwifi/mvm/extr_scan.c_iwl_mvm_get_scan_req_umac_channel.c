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
struct iwl_scan_umac_chan_param {int dummy; } ;
struct TYPE_8__ {struct iwl_scan_umac_chan_param channel; } ;
struct TYPE_7__ {struct iwl_scan_umac_chan_param channel; } ;
struct TYPE_6__ {struct iwl_scan_umac_chan_param channel; } ;
struct TYPE_5__ {struct iwl_scan_umac_chan_param channel; } ;
struct iwl_scan_req_umac {TYPE_4__ v1; TYPE_3__ v6; TYPE_2__ v7; TYPE_1__ v8; } ;
struct iwl_mvm {struct iwl_scan_req_umac* scan_cmd; } ;

/* Variables and functions */
 scalar_t__ iwl_mvm_cdb_scan_api (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adaptive_dwell_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adaptive_dwell_v2_supported (struct iwl_mvm*) ; 

__attribute__((used)) static inline struct iwl_scan_umac_chan_param *
iwl_mvm_get_scan_req_umac_channel(struct iwl_mvm *mvm)
{
	struct iwl_scan_req_umac *cmd = mvm->scan_cmd;

	if (iwl_mvm_is_adaptive_dwell_v2_supported(mvm))
		return &cmd->v8.channel;

	if (iwl_mvm_is_adaptive_dwell_supported(mvm))
		return &cmd->v7.channel;

	if (iwl_mvm_cdb_scan_api(mvm))
		return &cmd->v6.channel;

	return &cmd->v1.channel;
}
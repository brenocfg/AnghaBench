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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
typedef  enum iwl_mvm_traffic_load { ____Placeholder_iwl_mvm_traffic_load } iwl_mvm_traffic_load ;

/* Variables and functions */
 scalar_t__ IWL_MVM_TCM_LOAD_HIGH_THRESH ; 
 scalar_t__ IWL_MVM_TCM_LOAD_MEDIUM_THRESH ; 
 int IWL_MVM_TRAFFIC_HIGH ; 
 int IWL_MVM_TRAFFIC_LOW ; 
 int IWL_MVM_TRAFFIC_MEDIUM ; 
 scalar_t__ iwl_mvm_tcm_load_percentage (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static enum iwl_mvm_traffic_load
iwl_mvm_tcm_load(struct iwl_mvm *mvm, u32 airtime, unsigned long elapsed)
{
	u8 load = iwl_mvm_tcm_load_percentage(airtime, elapsed);

	if (load > IWL_MVM_TCM_LOAD_HIGH_THRESH)
		return IWL_MVM_TRAFFIC_HIGH;
	if (load > IWL_MVM_TCM_LOAD_MEDIUM_THRESH)
		return IWL_MVM_TRAFFIC_MEDIUM;

	return IWL_MVM_TRAFFIC_LOW;
}
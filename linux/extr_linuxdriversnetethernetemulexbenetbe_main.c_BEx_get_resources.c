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
struct be_resources {int max_vlans; int max_tx_qs; int max_evt_qs; int /*<<< orphan*/  if_cap_flags; scalar_t__ max_rss_qs; scalar_t__ max_rx_qs; int /*<<< orphan*/  member_0; int /*<<< orphan*/  max_mcast_mac; int /*<<< orphan*/  max_uc_mac; } ;
struct be_adapter {int port_num; int function_caps; scalar_t__ be3_native; int /*<<< orphan*/  function_mode; int /*<<< orphan*/  mc_type; scalar_t__ num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_PROFILE_TYPE ; 
 scalar_t__ BE2_MAX_RSS_QS ; 
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 int BE3_MAX_EVT_QS ; 
 scalar_t__ BE3_MAX_RSS_QS ; 
 void* BE3_MAX_TX_QS ; 
 int BE3_SRIOV_MAX_EVT_QS ; 
 int BE_FUNCTION_CAPS_RSS ; 
 int BE_FUNCTION_CAPS_SUPER_NIC ; 
 int /*<<< orphan*/  BE_IF_CAP_FLAGS_WANT ; 
 int /*<<< orphan*/  BE_IF_FLAGS_DEFQ_RSS ; 
 int /*<<< orphan*/  BE_IF_FLAGS_RSS ; 
 int /*<<< orphan*/  BE_MAX_MC ; 
 int BE_NUM_VLANS_SUPPORTED ; 
 int /*<<< orphan*/  BE_UC_PMAC_COUNT ; 
 int /*<<< orphan*/  BE_VF_UC_PMAC_COUNT ; 
 int /*<<< orphan*/  RESOURCE_LIMITS ; 
 int /*<<< orphan*/  be_cmd_get_profile_config (struct be_adapter*,struct be_resources*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_convert_mc_type (int /*<<< orphan*/ ) ; 
 scalar_t__ be_is_mc (struct be_adapter*) ; 
 scalar_t__ be_is_qnq_mode (struct be_adapter*) ; 
 scalar_t__ be_max_vfs (struct be_adapter*) ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 
 scalar_t__ be_virtfn (struct be_adapter*) ; 

__attribute__((used)) static void BEx_get_resources(struct be_adapter *adapter,
			      struct be_resources *res)
{
	bool use_sriov = adapter->num_vfs ? 1 : 0;

	if (be_physfn(adapter))
		res->max_uc_mac = BE_UC_PMAC_COUNT;
	else
		res->max_uc_mac = BE_VF_UC_PMAC_COUNT;

	adapter->mc_type = be_convert_mc_type(adapter->function_mode);

	if (be_is_mc(adapter)) {
		/* Assuming that there are 4 channels per port,
		 * when multi-channel is enabled
		 */
		if (be_is_qnq_mode(adapter))
			res->max_vlans = BE_NUM_VLANS_SUPPORTED/8;
		else
			/* In a non-qnq multichannel mode, the pvid
			 * takes up one vlan entry
			 */
			res->max_vlans = (BE_NUM_VLANS_SUPPORTED / 4) - 1;
	} else {
		res->max_vlans = BE_NUM_VLANS_SUPPORTED;
	}

	res->max_mcast_mac = BE_MAX_MC;

	/* 1) For BE3 1Gb ports, FW does not support multiple TXQs
	 * 2) Create multiple TX rings on a BE3-R multi-channel interface
	 *    *only* if it is RSS-capable.
	 */
	if (BE2_chip(adapter) || use_sriov ||  (adapter->port_num > 1) ||
	    be_virtfn(adapter) ||
	    (be_is_mc(adapter) &&
	     !(adapter->function_caps & BE_FUNCTION_CAPS_RSS))) {
		res->max_tx_qs = 1;
	} else if (adapter->function_caps & BE_FUNCTION_CAPS_SUPER_NIC) {
		struct be_resources super_nic_res = {0};

		/* On a SuperNIC profile, the driver needs to use the
		 * GET_PROFILE_CONFIG cmd to query the per-function TXQ limits
		 */
		be_cmd_get_profile_config(adapter, &super_nic_res, NULL,
					  ACTIVE_PROFILE_TYPE, RESOURCE_LIMITS,
					  0);
		/* Some old versions of BE3 FW don't report max_tx_qs value */
		res->max_tx_qs = super_nic_res.max_tx_qs ? : BE3_MAX_TX_QS;
	} else {
		res->max_tx_qs = BE3_MAX_TX_QS;
	}

	if ((adapter->function_caps & BE_FUNCTION_CAPS_RSS) &&
	    !use_sriov && be_physfn(adapter))
		res->max_rss_qs = (adapter->be3_native) ?
					   BE3_MAX_RSS_QS : BE2_MAX_RSS_QS;
	res->max_rx_qs = res->max_rss_qs + 1;

	if (be_physfn(adapter))
		res->max_evt_qs = (be_max_vfs(adapter) > 0) ?
					BE3_SRIOV_MAX_EVT_QS : BE3_MAX_EVT_QS;
	else
		res->max_evt_qs = 1;

	res->if_cap_flags = BE_IF_CAP_FLAGS_WANT;
	res->if_cap_flags &= ~BE_IF_FLAGS_DEFQ_RSS;
	if (!(adapter->function_caps & BE_FUNCTION_CAPS_RSS))
		res->if_cap_flags &= ~BE_IF_FLAGS_RSS;
}
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
typedef  int u32 ;
typedef  int u16 ;
struct be_resources {int vf_if_cap_flags; int max_rss_qs; int if_cap_flags; int max_rx_qs; int max_tx_qs; int max_cq_count; scalar_t__ max_uc_mac; scalar_t__ max_vlans; scalar_t__ max_iface_count; scalar_t__ max_mcc_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct be_adapter {struct be_resources pool_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_PROFILE_TYPE ; 
 int BE_IF_FLAGS_DEFQ_RSS ; 
 int BE_IF_FLAGS_RSS ; 
 int BE_IF_FLAGS_VLAN_PROMISCUOUS ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_MODIFIABLE ; 
 int /*<<< orphan*/  IF_CAPS_FLAGS_VALID_SHIFT ; 
 int /*<<< orphan*/  RESOURCE_MODIFIABLE ; 
 int /*<<< orphan*/  SH_VF_MAX_NIC_EQS ; 
 int /*<<< orphan*/  be_cmd_get_profile_config (struct be_adapter*,struct be_resources*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_max_pf_pool_rss_tables (struct be_adapter*) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void be_calculate_vf_res(struct be_adapter *adapter, u16 num_vfs,
				struct be_resources *vft_res)
{
	struct be_resources res = adapter->pool_res;
	u32 vf_if_cap_flags = res.vf_if_cap_flags;
	struct be_resources res_mod = {0};
	u16 num_vf_qs = 1;

	/* Distribute the queue resources among the PF and it's VFs */
	if (num_vfs) {
		/* Divide the rx queues evenly among the VFs and the PF, capped
		 * at VF-EQ-count. Any remainder queues belong to the PF.
		 */
		num_vf_qs = min(SH_VF_MAX_NIC_EQS,
				res.max_rss_qs / (num_vfs + 1));

		/* Skyhawk-R chip supports only MAX_PORT_RSS_TABLES
		 * RSS Tables per port. Provide RSS on VFs, only if number of
		 * VFs requested is less than it's PF Pool's RSS Tables limit.
		 */
		if (num_vfs >= be_max_pf_pool_rss_tables(adapter))
			num_vf_qs = 1;
	}

	/* Resource with fields set to all '1's by GET_PROFILE_CONFIG cmd,
	 * which are modifiable using SET_PROFILE_CONFIG cmd.
	 */
	be_cmd_get_profile_config(adapter, &res_mod, NULL, ACTIVE_PROFILE_TYPE,
				  RESOURCE_MODIFIABLE, 0);

	/* If RSS IFACE capability flags are modifiable for a VF, set the
	 * capability flag as valid and set RSS and DEFQ_RSS IFACE flags if
	 * more than 1 RSSQ is available for a VF.
	 * Otherwise, provision only 1 queue pair for VF.
	 */
	if (res_mod.vf_if_cap_flags & BE_IF_FLAGS_RSS) {
		vft_res->flags |= BIT(IF_CAPS_FLAGS_VALID_SHIFT);
		if (num_vf_qs > 1) {
			vf_if_cap_flags |= BE_IF_FLAGS_RSS;
			if (res.if_cap_flags & BE_IF_FLAGS_DEFQ_RSS)
				vf_if_cap_flags |= BE_IF_FLAGS_DEFQ_RSS;
		} else {
			vf_if_cap_flags &= ~(BE_IF_FLAGS_RSS |
					     BE_IF_FLAGS_DEFQ_RSS);
		}
	} else {
		num_vf_qs = 1;
	}

	if (res_mod.vf_if_cap_flags & BE_IF_FLAGS_VLAN_PROMISCUOUS) {
		vft_res->flags |= BIT(IF_CAPS_FLAGS_VALID_SHIFT);
		vf_if_cap_flags &= ~BE_IF_FLAGS_VLAN_PROMISCUOUS;
	}

	vft_res->vf_if_cap_flags = vf_if_cap_flags;
	vft_res->max_rx_qs = num_vf_qs;
	vft_res->max_rss_qs = num_vf_qs;
	vft_res->max_tx_qs = res.max_tx_qs / (num_vfs + 1);
	vft_res->max_cq_count = res.max_cq_count / (num_vfs + 1);

	/* Distribute unicast MACs, VLANs, IFACE count and MCCQ count equally
	 * among the PF and it's VFs, if the fields are changeable
	 */
	if (res_mod.max_uc_mac == FIELD_MODIFIABLE)
		vft_res->max_uc_mac = res.max_uc_mac / (num_vfs + 1);

	if (res_mod.max_vlans == FIELD_MODIFIABLE)
		vft_res->max_vlans = res.max_vlans / (num_vfs + 1);

	if (res_mod.max_iface_count == FIELD_MODIFIABLE)
		vft_res->max_iface_count = res.max_iface_count / (num_vfs + 1);

	if (res_mod.max_mcc_count == FIELD_MODIFIABLE)
		vft_res->max_mcc_count = res.max_mcc_count / (num_vfs + 1);
}
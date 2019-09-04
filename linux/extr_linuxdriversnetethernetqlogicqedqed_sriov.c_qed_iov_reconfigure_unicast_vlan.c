#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* vlans; } ;
struct qed_vf_info {int /*<<< orphan*/  relative_vf_id; int /*<<< orphan*/  opaque_fid; TYPE_2__ shadow_config; int /*<<< orphan*/  vport_id; } ;
struct qed_hwfn {int dummy; } ;
struct qed_filter_ucast {int is_rx_filter; int is_tx_filter; int /*<<< orphan*/  vlan; int /*<<< orphan*/  type; int /*<<< orphan*/  opcode; int /*<<< orphan*/  vport_to_add_to; } ;
typedef  int /*<<< orphan*/  filter ;
struct TYPE_3__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QED_ETH_VF_NUM_VLAN_FILTERS ; 
 int /*<<< orphan*/  QED_FILTER_ADD ; 
 int /*<<< orphan*/  QED_FILTER_VLAN ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  QED_SPQ_MODE_CB ; 
 int /*<<< orphan*/  memset (struct qed_filter_ucast*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_eth_filter_ucast (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_filter_ucast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_iov_reconfigure_unicast_vlan(struct qed_hwfn *p_hwfn,
					    struct qed_vf_info *p_vf)
{
	struct qed_filter_ucast filter;
	int rc = 0;
	int i;

	memset(&filter, 0, sizeof(filter));
	filter.is_rx_filter = 1;
	filter.is_tx_filter = 1;
	filter.vport_to_add_to = p_vf->vport_id;
	filter.opcode = QED_FILTER_ADD;

	/* Reconfigure vlans */
	for (i = 0; i < QED_ETH_VF_NUM_VLAN_FILTERS + 1; i++) {
		if (!p_vf->shadow_config.vlans[i].used)
			continue;

		filter.type = QED_FILTER_VLAN;
		filter.vlan = p_vf->shadow_config.vlans[i].vid;
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Reconfiguring VLAN [0x%04x] for VF [%04x]\n",
			   filter.vlan, p_vf->relative_vf_id);
		rc = qed_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					     &filter, QED_SPQ_MODE_CB, NULL);
		if (rc) {
			DP_NOTICE(p_hwfn,
				  "Failed to configure VLAN [%04x] to VF [%04x]\n",
				  filter.vlan, p_vf->relative_vf_id);
			break;
		}
	}

	return rc;
}
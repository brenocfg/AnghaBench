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
typedef  scalar_t__ u32 ;
struct qed_public_vf_info {scalar_t__ tx_rate; int /*<<< orphan*/  link_state; int /*<<< orphan*/  forced_vlan; int /*<<< orphan*/  mac; int /*<<< orphan*/  forced_mac; } ;
struct qed_mcp_link_state {scalar_t__ speed; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int /*<<< orphan*/ * hwfns; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  min_tx_rate; scalar_t__ max_tx_rate; int /*<<< orphan*/  linkstate; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  vlan; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 scalar_t__ IS_VF (struct qed_dev*) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_get_link (struct qed_hwfn*,int,int /*<<< orphan*/ *,struct qed_mcp_link_state*,int /*<<< orphan*/ *) ; 
 struct qed_public_vf_info* qed_iov_get_public_vf_info (struct qed_hwfn*,int,int) ; 
 int /*<<< orphan*/  qed_iov_get_vf_min_rate (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_iov_is_valid_vfid (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  qed_iov_spoofchk_get (struct qed_hwfn*,int) ; 

__attribute__((used)) static int qed_get_vf_config(struct qed_dev *cdev,
			     int vf_id, struct ifla_vf_info *ivi)
{
	struct qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	struct qed_public_vf_info *vf_info;
	struct qed_mcp_link_state link;
	u32 tx_rate;

	/* Sanitize request */
	if (IS_VF(cdev))
		return -EINVAL;

	if (!qed_iov_is_valid_vfid(&cdev->hwfns[0], vf_id, true, false)) {
		DP_VERBOSE(cdev, QED_MSG_IOV,
			   "VF index [%d] isn't active\n", vf_id);
		return -EINVAL;
	}

	vf_info = qed_iov_get_public_vf_info(hwfn, vf_id, true);

	qed_iov_get_link(hwfn, vf_id, NULL, &link, NULL);

	/* Fill information about VF */
	ivi->vf = vf_id;

	if (is_valid_ether_addr(vf_info->forced_mac))
		ether_addr_copy(ivi->mac, vf_info->forced_mac);
	else
		ether_addr_copy(ivi->mac, vf_info->mac);

	ivi->vlan = vf_info->forced_vlan;
	ivi->spoofchk = qed_iov_spoofchk_get(hwfn, vf_id);
	ivi->linkstate = vf_info->link_state;
	tx_rate = vf_info->tx_rate;
	ivi->max_tx_rate = tx_rate ? tx_rate : link.speed;
	ivi->min_tx_rate = qed_iov_get_vf_min_rate(hwfn, vf_id);

	return 0;
}
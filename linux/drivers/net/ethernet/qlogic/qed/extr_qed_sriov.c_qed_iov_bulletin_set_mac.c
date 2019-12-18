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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {scalar_t__ is_trusted_configured; } ;
struct TYPE_5__ {TYPE_1__* p_virt; } ;
struct qed_vf_info {TYPE_3__ p_vf_info; TYPE_2__ bulletin; scalar_t__ b_malicious; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct TYPE_4__ {int valid_bitmap; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAC_ADDR_FORCED ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  VFPF_BULLETIN_MAC_ADDR ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_iov_configure_vport_forced (struct qed_hwfn*,struct qed_vf_info*,int) ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_iov_bulletin_set_mac(struct qed_hwfn *p_hwfn, u8 *mac, int vfid)
{
	struct qed_vf_info *vf_info;
	u64 feature;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev, "Can not set MAC, invalid vfid [%d]\n",
			  vfid);
		return -EINVAL;
	}

	if (vf_info->b_malicious) {
		DP_NOTICE(p_hwfn->cdev, "Can't set MAC to malicious VF [%d]\n",
			  vfid);
		return -EINVAL;
	}

	if (vf_info->bulletin.p_virt->valid_bitmap & BIT(MAC_ADDR_FORCED)) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Can not set MAC, Forced MAC is configured\n");
		return -EINVAL;
	}

	feature = BIT(VFPF_BULLETIN_MAC_ADDR);
	ether_addr_copy(vf_info->bulletin.p_virt->mac, mac);

	vf_info->bulletin.p_virt->valid_bitmap |= feature;

	if (vf_info->p_vf_info.is_trusted_configured)
		qed_iov_configure_vport_forced(p_hwfn, vf_info, feature);

	return 0;
}
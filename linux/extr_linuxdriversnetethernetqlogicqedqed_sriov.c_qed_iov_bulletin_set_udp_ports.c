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
typedef  void* u16 ;
struct TYPE_4__ {TYPE_1__* p_virt; } ;
struct qed_vf_info {TYPE_2__ bulletin; scalar_t__ b_malicious; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct TYPE_3__ {void* geneve_udp_port; void* vxlan_udp_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,void*,int) ; 

void qed_iov_bulletin_set_udp_ports(struct qed_hwfn *p_hwfn,
				    int vfid, u16 vxlan_port, u16 geneve_port)
{
	struct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev,
			  "Can not set udp ports, invalid vfid [%d]\n", vfid);
		return;
	}

	if (vf_info->b_malicious) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Can not set udp ports to malicious VF [%d]\n",
			   vfid);
		return;
	}

	vf_info->bulletin.p_virt->vxlan_udp_port = vxlan_port;
	vf_info->bulletin.p_virt->geneve_udp_port = geneve_port;
}
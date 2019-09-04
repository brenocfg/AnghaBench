#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  msg_addr; } ;
union event_ring_data {int /*<<< orphan*/  malicious_vf; TYPE_1__ vf_pf_channel; } ;
typedef  int u8 ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  COMMON_EVENT_MALICIOUS_VF 129 
#define  COMMON_EVENT_VF_PF_CHANNEL 128 
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_sriov_vfpf_malicious (struct qed_hwfn*,int /*<<< orphan*/ *) ; 
 int qed_sriov_vfpf_msg (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_sriov_eqe_event(struct qed_hwfn *p_hwfn,
			       u8 opcode,
			       __le16 echo,
			       union event_ring_data *data, u8 fw_return_code)
{
	switch (opcode) {
	case COMMON_EVENT_VF_PF_CHANNEL:
		return qed_sriov_vfpf_msg(p_hwfn, le16_to_cpu(echo),
					  &data->vf_pf_channel.msg_addr);
	case COMMON_EVENT_MALICIOUS_VF:
		qed_sriov_vfpf_malicious(p_hwfn, &data->malicious_vf);
		return 0;
	default:
		DP_INFO(p_hwfn->cdev, "Unknown sriov eqe event 0x%02x\n",
			opcode);
		return -EINVAL;
	}
}
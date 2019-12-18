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
typedef  int u8 ;
typedef  int u16 ;
struct hnae3_handle {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct hclge_vport {int /*<<< orphan*/  state; TYPE_2__ port_base_vlan_cfg; struct hclge_dev* back; } ;
struct hclge_vlan_info {int vlan_tag; int qos; int /*<<< orphan*/  vlan_proto; } ;
struct hclge_dev {int num_alloc_vfs; struct hclge_vport* vport; TYPE_1__* pdev; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_3__ {int revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  HCLGE_VPORT_STATE_ALIVE ; 
 int /*<<< orphan*/  HNAE3_DOWN_CLIENT ; 
 int HNAE3_PORT_BASE_VLAN_NOCHANGE ; 
 int /*<<< orphan*/  HNAE3_UP_CLIENT ; 
 int VLAN_N_VID ; 
 int hclge_get_port_base_vlan_state (struct hclge_vport*,int /*<<< orphan*/ ,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_notify_client (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int hclge_push_vf_port_base_vlan_info (struct hclge_vport*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int hclge_update_port_base_vlan_cfg (struct hclge_vport*,int,struct hclge_vlan_info*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_set_vf_vlan_filter(struct hnae3_handle *handle, int vfid,
				    u16 vlan, u8 qos, __be16 proto)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct hclge_vlan_info vlan_info;
	u16 state;
	int ret;

	if (hdev->pdev->revision == 0x20)
		return -EOPNOTSUPP;

	/* qos is a 3 bits value, so can not be bigger than 7 */
	if (vfid >= hdev->num_alloc_vfs || vlan > VLAN_N_VID - 1 || qos > 7)
		return -EINVAL;
	if (proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	vport = &hdev->vport[vfid];
	state = hclge_get_port_base_vlan_state(vport,
					       vport->port_base_vlan_cfg.state,
					       vlan);
	if (state == HNAE3_PORT_BASE_VLAN_NOCHANGE)
		return 0;

	vlan_info.vlan_tag = vlan;
	vlan_info.qos = qos;
	vlan_info.vlan_proto = ntohs(proto);

	/* update port based VLAN for PF */
	if (!vfid) {
		hclge_notify_client(hdev, HNAE3_DOWN_CLIENT);
		ret = hclge_update_port_base_vlan_cfg(vport, state, &vlan_info);
		hclge_notify_client(hdev, HNAE3_UP_CLIENT);

		return ret;
	}

	if (!test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state)) {
		return hclge_update_port_base_vlan_cfg(vport, state,
						       &vlan_info);
	} else {
		ret = hclge_push_vf_port_base_vlan_info(&hdev->vport[0],
							(u8)vfid, state,
							vlan, qos,
							ntohs(proto));
		return ret;
	}
}
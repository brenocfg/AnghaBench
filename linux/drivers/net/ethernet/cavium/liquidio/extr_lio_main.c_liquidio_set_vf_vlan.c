#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_7__ {int param1; int param2; scalar_t__ more; int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct octnic_ctrl_pkt {int /*<<< orphan*/ * cb_fn; int /*<<< orphan*/  iq_no; TYPE_2__ ncmd; } ;
struct TYPE_12__ {int num_vfs_alloced; int* vf_vlantci; } ;
struct octeon_device {TYPE_6__ sriov_info; } ;
struct net_device {int dummy; } ;
struct TYPE_11__ {TYPE_4__* txpciq; } ;
struct lio {TYPE_5__ linfo; struct octeon_device* oct_dev; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_9__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_10__ {TYPE_3__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  OCTNET_CMD_ADD_VLAN_FILTER ; 
 int /*<<< orphan*/  OCTNET_CMD_DEL_VLAN_FILTER ; 
 int VLAN_N_VID ; 
 int VLAN_PRIO_SHIFT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct octnic_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int octnet_send_nic_ctrl_pkt (struct octeon_device*,struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static int liquidio_set_vf_vlan(struct net_device *netdev, int vfidx,
				u16 vlan, u8 qos, __be16 vlan_proto)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octnic_ctrl_pkt nctrl;
	u16 vlantci;
	int ret = 0;

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		return -EINVAL;

	if (vlan_proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	if (vlan >= VLAN_N_VID || qos > 7)
		return -EINVAL;

	if (vlan)
		vlantci = vlan | (u16)qos << VLAN_PRIO_SHIFT;
	else
		vlantci = 0;

	if (oct->sriov_info.vf_vlantci[vfidx] == vlantci)
		return 0;

	memset(&nctrl, 0, sizeof(struct octnic_ctrl_pkt));

	if (vlan)
		nctrl.ncmd.s.cmd = OCTNET_CMD_ADD_VLAN_FILTER;
	else
		nctrl.ncmd.s.cmd = OCTNET_CMD_DEL_VLAN_FILTER;

	nctrl.ncmd.s.param1 = vlantci;
	nctrl.ncmd.s.param2 =
	    vfidx + 1; /* vfidx is 0 based, but vf_num (param2) is 1 based */
	nctrl.ncmd.s.more = 0;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.cb_fn = NULL;

	ret = octnet_send_nic_ctrl_pkt(oct, &nctrl);
	if (ret) {
		if (ret > 0)
			ret = -EIO;
		return ret;
	}

	oct->sriov_info.vf_vlantci[vfidx] = vlantci;

	return ret;
}
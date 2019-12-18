#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int param1; int param2; scalar_t__ more; int /*<<< orphan*/  cmd; int /*<<< orphan*/  cmdgroup; } ;
struct TYPE_10__ {TYPE_2__ s; } ;
struct octnic_ctrl_pkt {int /*<<< orphan*/ * cb_fn; int /*<<< orphan*/  iq_no; TYPE_3__ ncmd; } ;
struct TYPE_14__ {int num_vfs_alloced; int* vf_spoofchk; } ;
struct TYPE_8__ {int app_cap_flags; } ;
struct octeon_device {TYPE_7__ sriov_info; TYPE_1__ fw_info; } ;
struct net_device {int dummy; } ;
struct TYPE_13__ {TYPE_5__* txpciq; } ;
struct lio {int /*<<< orphan*/  netdev; TYPE_6__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_12__ {TYPE_4__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int LIQUIDIO_SPOOFCHK_CAP ; 
 int /*<<< orphan*/  OCTNET_CMD_GROUP1 ; 
 int /*<<< orphan*/  OCTNET_CMD_SET_VF_SPOOFCHK ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  memset (struct octnic_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int octnet_send_nic_ctrl_pkt (struct octeon_device*,struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static int liquidio_set_vf_spoofchk(struct net_device *netdev, int vfidx,
				    bool enable)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octnic_ctrl_pkt nctrl;
	int retval;

	if (!(oct->fw_info.app_cap_flags & LIQUIDIO_SPOOFCHK_CAP)) {
		netif_info(lio, drv, lio->netdev,
			   "firmware does not support spoofchk\n");
		return -EOPNOTSUPP;
	}

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced) {
		netif_info(lio, drv, lio->netdev, "Invalid vfidx %d\n", vfidx);
		return -EINVAL;
	}

	if (enable) {
		if (oct->sriov_info.vf_spoofchk[vfidx])
			return 0;
	} else {
		/* Clear */
		if (!oct->sriov_info.vf_spoofchk[vfidx])
			return 0;
	}

	memset(&nctrl, 0, sizeof(struct octnic_ctrl_pkt));
	nctrl.ncmd.s.cmdgroup = OCTNET_CMD_GROUP1;
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_VF_SPOOFCHK;
	nctrl.ncmd.s.param1 =
		vfidx + 1; /* vfidx is 0 based,
			    * but vf_num (param1) is 1 based
			    */
	nctrl.ncmd.s.param2 = enable;
	nctrl.ncmd.s.more = 0;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.cb_fn = NULL;

	retval = octnet_send_nic_ctrl_pkt(oct, &nctrl);

	if (retval) {
		netif_info(lio, drv, lio->netdev,
			   "Failed to set VF %d spoofchk %s\n", vfidx,
			enable ? "on" : "off");
		return -1;
	}

	oct->sriov_info.vf_spoofchk[vfidx] = enable;
	netif_info(lio, drv, lio->netdev, "VF %u spoofchk is %s\n", vfidx,
		   enable ? "on" : "off");

	return 0;
}
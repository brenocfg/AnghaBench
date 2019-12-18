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
typedef  scalar_t__ u64 ;
struct TYPE_12__ {int param1; int param2; int /*<<< orphan*/  cmd; } ;
struct TYPE_13__ {TYPE_5__ s; scalar_t__ u64; } ;
struct octnic_ctrl_pkt {TYPE_6__ ncmd; int /*<<< orphan*/  cb_fn; scalar_t__ netpndev; int /*<<< orphan*/  iq_no; } ;
struct octeon_device {scalar_t__ chip_id; scalar_t__ tx_pause; scalar_t__ rx_pause; TYPE_7__* pci_dev; } ;
struct TYPE_8__ {scalar_t__ duplex; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
struct oct_link_info {TYPE_4__* txpciq; TYPE_2__ link; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; struct oct_link_info linfo; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_11__ {TYPE_3__ s; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 scalar_t__ OCTEON_CN23XX_PF_VID ; 
 int /*<<< orphan*/  OCTNET_CMD_SET_FLOW_CTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  liquidio_link_ctrl_cmd_completion ; 
 int /*<<< orphan*/  memset (struct octnic_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int octnet_send_nic_ctrl_pkt (struct octeon_device*,struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static int
lio_set_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	/* Notes: Not supporting any auto negotiation in these
	 * drivers.
	 */
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octnic_ctrl_pkt nctrl;
	struct oct_link_info *linfo = &lio->linfo;

	int ret = 0;

	if (oct->chip_id != OCTEON_CN23XX_PF_VID)
		return -EINVAL;

	if (linfo->link.s.duplex == 0) {
		/*no flow control for half duplex*/
		if (pause->rx_pause || pause->tx_pause)
			return -EINVAL;
	}

	/*do not support autoneg of link flow control*/
	if (pause->autoneg == AUTONEG_ENABLE)
		return -EINVAL;

	memset(&nctrl, 0, sizeof(struct octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_FLOW_CTL;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	if (pause->rx_pause) {
		/*enable rx pause*/
		nctrl.ncmd.s.param1 = 1;
	} else {
		/*disable rx pause*/
		nctrl.ncmd.s.param1 = 0;
	}

	if (pause->tx_pause) {
		/*enable tx pause*/
		nctrl.ncmd.s.param2 = 1;
	} else {
		/*disable tx pause*/
		nctrl.ncmd.s.param2 = 0;
	}

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	if (ret) {
		dev_err(&oct->pci_dev->dev,
			"Failed to set pause parameter, ret=%d\n", ret);
		return -EINVAL;
	}

	oct->rx_pause = pause->rx_pause;
	oct->tx_pause = pause->tx_pause;

	return 0;
}
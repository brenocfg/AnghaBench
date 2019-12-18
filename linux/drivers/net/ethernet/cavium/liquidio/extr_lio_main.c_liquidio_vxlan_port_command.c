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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int cmd; int /*<<< orphan*/  param1; int /*<<< orphan*/  more; } ;
struct TYPE_8__ {TYPE_1__ s; scalar_t__ u64; } ;
struct octnic_ctrl_pkt {int /*<<< orphan*/  cb_fn; scalar_t__ netpndev; int /*<<< orphan*/  iq_no; TYPE_2__ ncmd; } ;
struct octeon_device {TYPE_6__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_11__ {TYPE_4__* txpciq; } ;
struct lio {struct octeon_device* oct_dev; TYPE_5__ linfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_10__ {TYPE_3__ s; } ;

/* Variables and functions */
 int EIO ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  liquidio_link_ctrl_cmd_completion ; 
 int /*<<< orphan*/  memset (struct octnic_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int octnet_send_nic_ctrl_pkt (struct octeon_device*,struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static int liquidio_vxlan_port_command(struct net_device *netdev, int command,
				       u16 vxlan_port, u8 vxlan_cmd_bit)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octnic_ctrl_pkt nctrl;
	int ret = 0;

	memset(&nctrl, 0, sizeof(struct octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = command;
	nctrl.ncmd.s.more = vxlan_cmd_bit;
	nctrl.ncmd.s.param1 = vxlan_port;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	if (ret) {
		dev_err(&oct->pci_dev->dev,
			"VxLAN port add/delete failed in core (ret:0x%x)\n",
			ret);
		if (ret > 0)
			ret = -EIO;
	}
	return ret;
}
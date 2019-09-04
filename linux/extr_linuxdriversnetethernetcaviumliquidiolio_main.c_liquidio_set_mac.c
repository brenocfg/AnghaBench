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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct TYPE_7__ {int more; scalar_t__ param1; int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {TYPE_1__ s; scalar_t__ u64; } ;
struct octnic_ctrl_pkt {int wait_time; scalar_t__* udd; int /*<<< orphan*/  cb_fn; scalar_t__ netpndev; int /*<<< orphan*/  iq_no; TYPE_2__ ncmd; } ;
struct octeon_device {TYPE_5__* pci_dev; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  hw_addr; TYPE_4__* txpciq; } ;
struct lio {TYPE_6__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_10__ {TYPE_3__ s; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  OCTNET_CMD_CHANGE_MACADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  liquidio_link_ctrl_cmd_completion ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct octnic_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int octnet_send_nic_ctrl_pkt (struct octeon_device*,struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static int liquidio_set_mac(struct net_device *netdev, void *p)
{
	int ret = 0;
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct sockaddr *addr = (struct sockaddr *)p;
	struct octnic_ctrl_pkt nctrl;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memset(&nctrl, 0, sizeof(struct octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_CHANGE_MACADDR;
	nctrl.ncmd.s.param1 = 0;
	nctrl.ncmd.s.more = 1;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;
	nctrl.wait_time = 100;

	nctrl.udd[0] = 0;
	/* The MAC Address is presented in network byte order. */
	memcpy((u8 *)&nctrl.udd[0] + 2, addr->sa_data, ETH_ALEN);

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	if (ret < 0) {
		dev_err(&oct->pci_dev->dev, "MAC Address change failed\n");
		return -ENOMEM;
	}
	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	memcpy(((u8 *)&lio->linfo.hw_addr) + 2, addr->sa_data, ETH_ALEN);

	return 0;
}
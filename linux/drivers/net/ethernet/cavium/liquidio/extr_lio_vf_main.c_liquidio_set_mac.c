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
struct octnic_ctrl_pkt {scalar_t__ sc_status; scalar_t__* udd; scalar_t__ netpndev; int /*<<< orphan*/  iq_no; TYPE_2__ ncmd; } ;
struct octeon_device {TYPE_5__* pci_dev; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  hw_addr; TYPE_4__* txpciq; scalar_t__ macaddr_is_admin_asgnd; } ;
struct lio {TYPE_6__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_10__ {TYPE_3__ s; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ FIRMWARE_STATUS_CODE (int /*<<< orphan*/ ) ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  OCTEON_REQUEST_NO_PERMISSION ; 
 int /*<<< orphan*/  OCTNET_CMD_CHANGE_MACADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct octnic_ctrl_pkt*,int /*<<< orphan*/ ,int) ; 
 int octnet_send_nic_ctrl_pkt (struct octeon_device*,struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static int liquidio_set_mac(struct net_device *netdev, void *p)
{
	struct sockaddr *addr = (struct sockaddr *)p;
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octnic_ctrl_pkt nctrl;
	int ret = 0;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(addr->sa_data, netdev->dev_addr))
		return 0;

	if (lio->linfo.macaddr_is_admin_asgnd)
		return -EPERM;

	memset(&nctrl, 0, sizeof(struct octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_CHANGE_MACADDR;
	nctrl.ncmd.s.param1 = 0;
	nctrl.ncmd.s.more = 1;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;

	nctrl.udd[0] = 0;
	/* The MAC Address is presented in network byte order. */
	ether_addr_copy((u8 *)&nctrl.udd[0] + 2, addr->sa_data);

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	if (ret < 0) {
		dev_err(&oct->pci_dev->dev, "MAC Address change failed\n");
		return -ENOMEM;
	}

	if (nctrl.sc_status ==
	    FIRMWARE_STATUS_CODE(OCTEON_REQUEST_NO_PERMISSION)) {
		dev_err(&oct->pci_dev->dev, "MAC Address change failed: no permission\n");
		return -EPERM;
	}

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	ether_addr_copy(((u8 *)&lio->linfo.hw_addr) + 2, addr->sa_data);

	return 0;
}
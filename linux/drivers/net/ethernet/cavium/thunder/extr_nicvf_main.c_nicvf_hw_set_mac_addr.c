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
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ mac; } ;
struct nicvf {int /*<<< orphan*/  vf_id; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_SET_MAC ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static int nicvf_hw_set_mac_addr(struct nicvf *nic, struct net_device *netdev)
{
	union nic_mbx mbx = {};

	mbx.mac.msg = NIC_MBOX_MSG_SET_MAC;
	mbx.mac.vf_id = nic->vf_id;
	ether_addr_copy(mbx.mac.mac_addr, netdev->dev_addr);

	return nicvf_send_msg_to_pf(nic, &mbx);
}
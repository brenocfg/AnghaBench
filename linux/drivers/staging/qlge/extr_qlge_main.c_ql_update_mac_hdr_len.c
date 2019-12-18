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
typedef  scalar_t__ u16 ;
struct ql_adapter {TYPE_1__* ndev; } ;
struct ib_mac_iocb_rsp {int flags2; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 scalar_t__ ETH_P_8021Q ; 
 int IB_MAC_IOCB_RSP_V ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int VLAN_HLEN ; 

__attribute__((used)) static void ql_update_mac_hdr_len(struct ql_adapter *qdev,
				  struct ib_mac_iocb_rsp *ib_mac_rsp,
				  void *page, size_t *len)
{
	u16 *tags;

	if (qdev->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)
		return;
	if (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_V) {
		tags = (u16 *)page;
		/* Look for stacked vlan tags in ethertype field */
		if (tags[6] == ETH_P_8021Q &&
		    tags[8] == ETH_P_8021Q)
			*len += 2 * VLAN_HLEN;
		else
			*len += VLAN_HLEN;
	}
}
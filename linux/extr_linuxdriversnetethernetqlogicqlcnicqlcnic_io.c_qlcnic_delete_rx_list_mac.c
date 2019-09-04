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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct qlcnic_filter {int /*<<< orphan*/  fnode; } ;
struct TYPE_2__ {int /*<<< orphan*/  fnum; } ;
struct qlcnic_adapter {TYPE_1__ rx_fhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int /*<<< orphan*/  QLCNIC_MAC_DEL ; 
 int /*<<< orphan*/  QLCNIC_MAC_VLAN_ADD ; 
 int /*<<< orphan*/  QLCNIC_MAC_VLAN_DEL ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int qlcnic_sre_macaddr_change (struct qlcnic_adapter*,void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_delete_rx_list_mac(struct qlcnic_adapter *adapter,
				      struct qlcnic_filter *fil,
				      void *addr, u16 vlan_id)
{
	int ret;
	u8 op;

	op = vlan_id ? QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_ADD;
	ret = qlcnic_sre_macaddr_change(adapter, addr, vlan_id, op);
	if (ret)
		return;

	op = vlan_id ? QLCNIC_MAC_VLAN_DEL : QLCNIC_MAC_DEL;
	ret = qlcnic_sre_macaddr_change(adapter, addr, vlan_id, op);
	if (!ret) {
		hlist_del(&fil->fnode);
		adapter->rx_fhash.fnum--;
	}
}
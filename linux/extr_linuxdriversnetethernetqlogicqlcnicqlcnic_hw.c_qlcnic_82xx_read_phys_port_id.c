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
struct qlcnic_adapter {int /*<<< orphan*/  flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys_port_id; int /*<<< orphan*/  physical_port; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  QLCNIC_HAS_PHYS_PORT_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int qlcnic_get_mac_address (struct qlcnic_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qlcnic_82xx_read_phys_port_id(struct qlcnic_adapter *adapter)
{
	u8 mac[ETH_ALEN];
	int ret;

	ret = qlcnic_get_mac_address(adapter, mac,
				     adapter->ahw->physical_port);
	if (ret)
		return ret;

	memcpy(adapter->ahw->phys_port_id, mac, ETH_ALEN);
	adapter->flags |= QLCNIC_HAS_PHYS_PORT_ID;

	return 0;
}
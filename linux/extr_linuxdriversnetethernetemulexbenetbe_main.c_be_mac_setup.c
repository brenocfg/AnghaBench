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
struct be_adapter {int /*<<< orphan*/  dev_mac; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int ETH_ALEN ; 
 int be_cmd_get_perm_mac (struct be_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ be_virtfn (struct be_adapter*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int be_mac_setup(struct be_adapter *adapter)
{
	u8 mac[ETH_ALEN];
	int status;

	if (is_zero_ether_addr(adapter->netdev->dev_addr)) {
		status = be_cmd_get_perm_mac(adapter, mac);
		if (status)
			return status;

		memcpy(adapter->netdev->dev_addr, mac, ETH_ALEN);
		memcpy(adapter->netdev->perm_addr, mac, ETH_ALEN);

		/* Initial MAC for BE3 VFs is already programmed by PF */
		if (BEx_chip(adapter) && be_virtfn(adapter))
			memcpy(adapter->dev_mac, mac, ETH_ALEN);
	}

	return 0;
}
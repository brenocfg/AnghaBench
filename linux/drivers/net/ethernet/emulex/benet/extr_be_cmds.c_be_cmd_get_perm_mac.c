#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct be_adapter {int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int be_cmd_get_mac_from_list (struct be_adapter*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_cmd_mac_addr_query (struct be_adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 

int be_cmd_get_perm_mac(struct be_adapter *adapter, u8 *mac)
{
	int status;
	bool pmac_valid = false;

	eth_zero_addr(mac);

	if (BEx_chip(adapter)) {
		if (be_physfn(adapter))
			status = be_cmd_mac_addr_query(adapter, mac, true, 0,
						       0);
		else
			status = be_cmd_mac_addr_query(adapter, mac, false,
						       adapter->if_handle, 0);
	} else {
		status = be_cmd_get_mac_from_list(adapter, mac, &pmac_valid,
						  NULL, adapter->if_handle, 0);
	}

	return status;
}
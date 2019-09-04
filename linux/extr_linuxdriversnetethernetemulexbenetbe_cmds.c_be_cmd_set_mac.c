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
typedef  int /*<<< orphan*/  u32 ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int be_cmd_get_mac_from_list (struct be_adapter*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_pmac_del (struct be_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_cmd_set_mac_list (struct be_adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int be_cmd_set_mac(struct be_adapter *adapter, u8 *mac, int if_id, u32 dom)
{
	bool active_mac = false;
	u8 old_mac[ETH_ALEN];
	u32 pmac_id;
	int status;

	status = be_cmd_get_mac_from_list(adapter, old_mac, &active_mac,
					  &pmac_id, if_id, dom);

	if (!status && active_mac)
		be_cmd_pmac_del(adapter, if_id, pmac_id, dom);

	return be_cmd_set_mac_list(adapter, mac, mac ? 1 : 0, dom);
}
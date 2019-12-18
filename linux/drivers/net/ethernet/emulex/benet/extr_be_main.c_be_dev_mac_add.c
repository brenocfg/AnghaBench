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
struct be_adapter {int uc_macs; int /*<<< orphan*/ * pmac_id; int /*<<< orphan*/  if_handle; TYPE_1__* uc_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int be_cmd_pmac_add (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int be_dev_mac_add(struct be_adapter *adapter, u8 *mac)
{
	int i;

	/* Check if mac has already been added as part of uc-list */
	for (i = 0; i < adapter->uc_macs; i++) {
		if (ether_addr_equal(adapter->uc_list[i].mac, mac)) {
			/* mac already added, skip addition */
			adapter->pmac_id[0] = adapter->pmac_id[i + 1];
			return 0;
		}
	}

	return be_cmd_pmac_add(adapter, mac, adapter->if_handle,
			       &adapter->pmac_id[0], 0);
}
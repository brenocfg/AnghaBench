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
struct be_adapter {int /*<<< orphan*/ * pmac_id; int /*<<< orphan*/  if_handle; TYPE_1__* uc_list; int /*<<< orphan*/  dev_mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int be_cmd_pmac_add (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_uc_mac_add(struct be_adapter *adapter, int uc_idx)
{
	if (ether_addr_equal(adapter->uc_list[uc_idx].mac, adapter->dev_mac)) {
		adapter->pmac_id[uc_idx + 1] = adapter->pmac_id[0];
		return 0;
	}

	return be_cmd_pmac_add(adapter, adapter->uc_list[uc_idx].mac,
			       adapter->if_handle,
			       &adapter->pmac_id[uc_idx + 1], 0);
}
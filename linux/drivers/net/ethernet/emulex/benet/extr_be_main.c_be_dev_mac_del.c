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
struct be_adapter {int uc_macs; int* pmac_id; int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cmd_pmac_del (struct be_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_dev_mac_del(struct be_adapter *adapter, int pmac_id)
{
	int i;

	/* Skip deletion if the programmed mac is
	 * being used in uc-list
	 */
	for (i = 0; i < adapter->uc_macs; i++) {
		if (adapter->pmac_id[i + 1] == pmac_id)
			return;
	}
	be_cmd_pmac_del(adapter, adapter->if_handle, pmac_id, 0);
}
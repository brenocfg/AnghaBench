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
struct be_adapter {int* pmac_id; int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cmd_pmac_del (struct be_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_uc_mac_del(struct be_adapter *adapter, int pmac_id)
{
	if (pmac_id == adapter->pmac_id[0])
		return;

	be_cmd_pmac_del(adapter, adapter->if_handle, pmac_id, 0);
}
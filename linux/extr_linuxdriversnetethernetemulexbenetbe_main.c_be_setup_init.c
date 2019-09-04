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
struct TYPE_2__ {int link_speed; } ;
struct be_adapter {int vlan_prio_bmap; int if_handle; int be3_native; int /*<<< orphan*/  cmd_privileges; int /*<<< orphan*/  phy_state; scalar_t__ if_flags; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_UNKNOWN_PHY_STATE ; 
 int /*<<< orphan*/  MAX_PRIVILEGES ; 
 int /*<<< orphan*/  MIN_PRIVILEGES ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 

__attribute__((used)) static void be_setup_init(struct be_adapter *adapter)
{
	adapter->vlan_prio_bmap = 0xff;
	adapter->phy.link_speed = -1;
	adapter->if_handle = -1;
	adapter->be3_native = false;
	adapter->if_flags = 0;
	adapter->phy_state = BE_UNKNOWN_PHY_STATE;
	if (be_physfn(adapter))
		adapter->cmd_privileges = MAX_PRIVILEGES;
	else
		adapter->cmd_privileges = MIN_PRIVILEGES;
}
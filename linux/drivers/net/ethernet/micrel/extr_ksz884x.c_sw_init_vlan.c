#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ksz_switch {TYPE_2__* port_cfg; TYPE_1__* vlan_table; } ;
struct ksz_hw {struct ksz_switch* ksz_switch; } ;
struct TYPE_4__ {int /*<<< orphan*/  member; int /*<<< orphan*/  vid; } ;
struct TYPE_3__ {int /*<<< orphan*/  member; int /*<<< orphan*/  fid; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_MASK ; 
 int TOTAL_PORT_NUM ; 
 int VLAN_TABLE_ENTRIES ; 
 int /*<<< orphan*/  port_get_def_vid (struct ksz_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sw_r_vlan_table (struct ksz_hw*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sw_init_vlan(struct ksz_hw *hw)
{
	int port;
	int entry;
	struct ksz_switch *sw = hw->ksz_switch;

	/* Read 16 VLAN entries from device's VLAN table. */
	for (entry = 0; entry < VLAN_TABLE_ENTRIES; entry++) {
		sw_r_vlan_table(hw, entry,
			&sw->vlan_table[entry].vid,
			&sw->vlan_table[entry].fid,
			&sw->vlan_table[entry].member);
	}

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		port_get_def_vid(hw, port, &sw->port_cfg[port].vid);
		sw->port_cfg[port].member = PORT_MASK;
	}
}
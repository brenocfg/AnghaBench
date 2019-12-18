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
struct ksz_mac_table {int* mac_addr; int override; int valid; int /*<<< orphan*/  fid; int /*<<< orphan*/  use_fid; int /*<<< orphan*/  ports; } ;
struct ksz_hw {TYPE_1__* ksz_switch; } ;
struct TYPE_2__ {struct ksz_mac_table* mac_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_MASK ; 
 size_t STP_ENTRY ; 
 int /*<<< orphan*/  sw_w_sta_mac_table (struct ksz_hw*,size_t,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sw_init_stp(struct ksz_hw *hw)
{
	struct ksz_mac_table *entry;

	entry = &hw->ksz_switch->mac_table[STP_ENTRY];
	entry->mac_addr[0] = 0x01;
	entry->mac_addr[1] = 0x80;
	entry->mac_addr[2] = 0xC2;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x00;
	entry->ports = HOST_MASK;
	entry->override = 1;
	entry->valid = 1;
	sw_w_sta_mac_table(hw, STP_ENTRY,
		entry->mac_addr, entry->ports,
		entry->override, entry->valid,
		entry->use_fid, entry->fid);
}
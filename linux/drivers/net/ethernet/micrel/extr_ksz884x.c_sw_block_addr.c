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
struct ksz_mac_table {int /*<<< orphan*/  fid; int /*<<< orphan*/  use_fid; scalar_t__ valid; int /*<<< orphan*/  override; int /*<<< orphan*/  ports; int /*<<< orphan*/  mac_addr; } ;
struct ksz_hw {TYPE_1__* ksz_switch; } ;
struct TYPE_2__ {struct ksz_mac_table* mac_table; } ;

/* Variables and functions */
 int BROADCAST_ENTRY ; 
 int IPV6_ADDR_ENTRY ; 
 int /*<<< orphan*/  sw_w_sta_mac_table (struct ksz_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sw_block_addr(struct ksz_hw *hw)
{
	struct ksz_mac_table *entry;
	int i;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		entry = &hw->ksz_switch->mac_table[i];
		entry->valid = 0;
		sw_w_sta_mac_table(hw, i,
			entry->mac_addr, entry->ports,
			entry->override, entry->valid,
			entry->use_fid, entry->fid);
	}
}
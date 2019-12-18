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
struct sr_pcie_phy_core {size_t pipemux; } ;
struct sr_pcie_phy {unsigned int index; struct sr_pcie_phy_core* core; } ;

/* Variables and functions */
 unsigned int* pipemux_table ; 

__attribute__((used)) static bool pcie_core_is_for_rc(struct sr_pcie_phy *phy)
{
	struct sr_pcie_phy_core *core = phy->core;
	unsigned int core_idx = phy->index;

	return !!((pipemux_table[core->pipemux] >> core_idx) & 0x1);
}
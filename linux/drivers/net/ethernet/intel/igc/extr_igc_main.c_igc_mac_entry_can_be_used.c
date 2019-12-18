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
typedef  int u8 ;
struct igc_mac_addr {int state; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int IGC_MAC_STATE_IN_USE ; 
 int const IGC_MAC_STATE_SRC_ADDR ; 
 int /*<<< orphan*/  ether_addr_equal (int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool igc_mac_entry_can_be_used(const struct igc_mac_addr *entry,
				      const u8 *addr, const u8 flags)
{
	if (!(entry->state & IGC_MAC_STATE_IN_USE))
		return true;

	if ((entry->state & IGC_MAC_STATE_SRC_ADDR) !=
	    (flags & IGC_MAC_STATE_SRC_ADDR))
		return false;

	if (!ether_addr_equal(addr, entry->addr))
		return false;

	return true;
}
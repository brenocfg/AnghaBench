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
struct et131x_adapter {int /*<<< orphan*/ * rom_addr; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_hwaddr_init(struct et131x_adapter *adapter)
{
	/* If have our default mac from init and no mac address from
	 * EEPROM then we need to generate the last octet and set it on the
	 * device
	 */
	if (is_zero_ether_addr(adapter->rom_addr)) {
		/* We need to randomly generate the last octet so we
		 * decrease our chances of setting the mac address to
		 * same as another one of our cards in the system
		 */
		get_random_bytes(&adapter->addr[5], 1);
		/* We have the default value in the register we are
		 * working with so we need to copy the current
		 * address into the permanent address
		 */
		ether_addr_copy(adapter->rom_addr, adapter->addr);
	} else {
		/* We do not have an override address, so set the
		 * current address to the permanent address and add
		 * it to the device
		 */
		ether_addr_copy(adapter->addr, adapter->rom_addr);
	}
}
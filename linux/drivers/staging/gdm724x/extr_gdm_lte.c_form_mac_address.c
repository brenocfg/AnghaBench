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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  eth_random_addr (scalar_t__*) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__*,scalar_t__*) ; 
 scalar_t__* gdm_lte_macaddr ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void form_mac_address(u8 *dev_addr, u8 *nic_src, u8 *nic_dest,
			     u8 *mac_address, u8 index)
{
	/* Form the dev_addr */
	if (!mac_address)
		ether_addr_copy(dev_addr, gdm_lte_macaddr);
	else
		ether_addr_copy(dev_addr, mac_address);

	/* The last byte of the mac address
	 * should be less than or equal to 0xFC
	 */
	dev_addr[ETH_ALEN - 1] += index;

	/* Create random nic src and copy the first
	 * 3 bytes to be the same as dev_addr
	 */
	eth_random_addr(nic_src);
	memcpy(nic_src, dev_addr, 3);

	/* Copy the nic_dest from dev_addr*/
	ether_addr_copy(nic_dest, dev_addr);
}
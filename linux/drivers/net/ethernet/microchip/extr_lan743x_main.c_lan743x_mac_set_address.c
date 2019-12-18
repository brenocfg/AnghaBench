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
typedef  int u32 ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mac_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_RX_ADDRH ; 
 int /*<<< orphan*/  MAC_RX_ADDRL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_info (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void lan743x_mac_set_address(struct lan743x_adapter *adapter,
				    u8 *addr)
{
	u32 addr_lo, addr_hi;

	addr_lo = addr[0] |
		addr[1] << 8 |
		addr[2] << 16 |
		addr[3] << 24;
	addr_hi = addr[4] |
		addr[5] << 8;
	lan743x_csr_write(adapter, MAC_RX_ADDRL, addr_lo);
	lan743x_csr_write(adapter, MAC_RX_ADDRH, addr_hi);

	ether_addr_copy(adapter->mac_address, addr);
	netif_info(adapter, drv, adapter->netdev,
		   "MAC address set to %pM\n", addr);
}
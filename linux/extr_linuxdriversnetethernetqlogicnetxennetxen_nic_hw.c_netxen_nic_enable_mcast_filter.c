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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u32 ;
typedef  int u16 ;
struct netxen_adapter {int physical_port; int mc_enabled; int /*<<< orphan*/ * mac_addr; } ;

/* Variables and functions */
 unsigned long MAC_HI (int /*<<< orphan*/ *) ; 
 unsigned long MAC_LO (int /*<<< orphan*/ *) ; 
 scalar_t__ NETXEN_MAC_ADDR_CNTL_REG ; 
 scalar_t__ NETXEN_UNICAST_ADDR (int,int) ; 
 unsigned long NXRD32 (struct netxen_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,scalar_t__,unsigned long) ; 

__attribute__((used)) static int
netxen_nic_enable_mcast_filter(struct netxen_adapter *adapter)
{
	u32	val = 0;
	u16 port = adapter->physical_port;
	u8 *addr = adapter->mac_addr;

	if (adapter->mc_enabled)
		return 0;

	val = NXRD32(adapter, NETXEN_MAC_ADDR_CNTL_REG);
	val |= (1UL << (28+port));
	NXWR32(adapter, NETXEN_MAC_ADDR_CNTL_REG, val);

	/* add broadcast addr to filter */
	val = 0xffffff;
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0), val);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0)+4, val);

	/* add station addr to filter */
	val = MAC_HI(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1), val);
	val = MAC_LO(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1)+4, val);

	adapter->mc_enabled = 1;
	return 0;
}
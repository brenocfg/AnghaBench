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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct netxen_adapter {int /*<<< orphan*/  physical_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_HI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAC_LO (int /*<<< orphan*/ *) ; 
 scalar_t__ NETXEN_MCAST_ADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netxen_nic_set_mcast_addr(struct netxen_adapter *adapter,
		int index, u8 *addr)
{
	u32 hi = 0, lo = 0;
	u16 port = adapter->physical_port;

	lo = MAC_LO(addr);
	hi = MAC_HI(addr);

	NXWR32(adapter, NETXEN_MCAST_ADDR(port, index), hi);
	NXWR32(adapter, NETXEN_MCAST_ADDR(port, index)+4, lo);

	return 0;
}
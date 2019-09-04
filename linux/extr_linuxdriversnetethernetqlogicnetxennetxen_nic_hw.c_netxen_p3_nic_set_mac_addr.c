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
struct netxen_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netxen_p3_nic_set_multi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netxen_p3_nic_set_mac_addr(struct netxen_adapter *adapter, u8 *addr)
{
	/* assuming caller has already copied new addr to netdev */
	netxen_p3_nic_set_multi(adapter->netdev);
	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {TYPE_1__** port; } ;
struct TYPE_2__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void t4_set_hw_addr(struct adapter *adapter, int port_idx,
				  u8 hw_addr[])
{
	ether_addr_copy(adapter->port[port_idx]->dev_addr, hw_addr);
	ether_addr_copy(adapter->port[port_idx]->perm_addr, hw_addr);
}
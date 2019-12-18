#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct net_device {scalar_t__* dev_addr; } ;
struct TYPE_3__ {int mac_addr; } ;
struct TYPE_4__ {TYPE_1__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,scalar_t__*) ; 
 TYPE_2__* mace ; 

__attribute__((used)) static inline void load_eaddr(struct net_device *dev)
{
	int i;
	u64 macaddr;

	DPRINTK("Loading MAC Address: %pM\n", dev->dev_addr);
	macaddr = 0;
	for (i = 0; i < 6; i++)
		macaddr |= (u64)dev->dev_addr[i] << ((5 - i) * 8);

	mace->eth.mac_addr = macaddr;
}
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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int MACSONIC_DAYNA ; 
 int /*<<< orphan*/  SONIC_READ_PROM (int) ; 
 int /*<<< orphan*/  bit_reverse_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mac_sonic_nubus_ethernet_addr(struct net_device *dev,
					 unsigned long prom_addr, int id)
{
	int i;
	for(i = 0; i < 6; i++)
		dev->dev_addr[i] = SONIC_READ_PROM(i);

	/* Some of the addresses are bit-reversed */
	if (id != MACSONIC_DAYNA)
		bit_reverse_addr(dev->dev_addr);

	return 0;
}
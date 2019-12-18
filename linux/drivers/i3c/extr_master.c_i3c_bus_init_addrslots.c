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
struct i3c_bus {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  I3C_ADDR_SLOT_RSVD ; 
 int I3C_BROADCAST_ADDR ; 
 int /*<<< orphan*/  i3c_bus_set_addr_slot_status (struct i3c_bus*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i3c_bus_init_addrslots(struct i3c_bus *bus)
{
	int i;

	/* Addresses 0 to 7 are reserved. */
	for (i = 0; i < 8; i++)
		i3c_bus_set_addr_slot_status(bus, i, I3C_ADDR_SLOT_RSVD);

	/*
	 * Reserve broadcast address and all addresses that might collide
	 * with the broadcast address when facing a single bit error.
	 */
	i3c_bus_set_addr_slot_status(bus, I3C_BROADCAST_ADDR,
				     I3C_ADDR_SLOT_RSVD);
	for (i = 0; i < 7; i++)
		i3c_bus_set_addr_slot_status(bus, I3C_BROADCAST_ADDR ^ BIT(i),
					     I3C_ADDR_SLOT_RSVD);
}
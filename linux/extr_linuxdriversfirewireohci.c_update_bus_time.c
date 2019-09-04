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
typedef  int u32 ;
struct fw_ohci {int bus_time_running; int bus_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IntMaskSet ; 
 int /*<<< orphan*/  OHCI1394_cycle64Seconds ; 
 int get_cycle_time (struct fw_ohci*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 update_bus_time(struct fw_ohci *ohci)
{
	u32 cycle_time_seconds = get_cycle_time(ohci) >> 25;

	if (unlikely(!ohci->bus_time_running)) {
		reg_write(ohci, OHCI1394_IntMaskSet, OHCI1394_cycle64Seconds);
		ohci->bus_time = (lower_32_bits(get_seconds()) & ~0x7f) |
		                 (cycle_time_seconds & 0x40);
		ohci->bus_time_running = true;
	}

	if ((ohci->bus_time & 0x40) != (cycle_time_seconds & 0x40))
		ohci->bus_time += 0x40;

	return ohci->bus_time | cycle_time_seconds;
}
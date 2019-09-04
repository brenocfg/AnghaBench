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
struct IO_APIC_route_entry {int dummy; } ;
union entry_union {struct IO_APIC_route_entry entry; void* w2; void* w1; } ;

/* Variables and functions */
 void* io_apic_read (int,int) ; 

__attribute__((used)) static struct IO_APIC_route_entry __ioapic_read_entry(int apic, int pin)
{
	union entry_union eu;

	eu.w1 = io_apic_read(apic, 0x10 + 2 * pin);
	eu.w2 = io_apic_read(apic, 0x11 + 2 * pin);

	return eu.entry;
}
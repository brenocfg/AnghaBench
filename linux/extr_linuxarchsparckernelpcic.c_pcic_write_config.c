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
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pcic_read_config_dword (scalar_t__,unsigned int,int,unsigned int*) ; 
 int pcic_write_config_dword (scalar_t__,unsigned int,int,int) ; 

__attribute__((used)) static int pcic_write_config(struct pci_bus *bus, unsigned int devfn,
   int where, int size, u32 val)
{
	unsigned int v;

	if (bus->number != 0) return -EINVAL;
	switch (size) {
	case 1:
		pcic_read_config_dword(bus->number, devfn, where&~3, &v);
		v = (v & ~(0xff << (8*(where&3)))) |
		    ((0xff&val) << (8*(where&3)));
		return pcic_write_config_dword(bus->number, devfn, where&~3, v);
	case 2:
		if (where&1) return -EINVAL;
		pcic_read_config_dword(bus->number, devfn, where&~3, &v);
		v = (v & ~(0xffff << (8*(where&3)))) |
		    ((0xffff&val) << (8*(where&3)));
		return pcic_write_config_dword(bus->number, devfn, where&~3, v);
	case 4:
		if (where&3) return -EINVAL;
		return pcic_write_config_dword(bus->number, devfn, where, val);
	}
	return -EINVAL;
}
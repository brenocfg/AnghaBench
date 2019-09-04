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
typedef  unsigned int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 rt3883_pci_get_cfgaddr(unsigned int bus, unsigned int slot,
					 unsigned int func, unsigned int where)
{
	return (bus << 16) | (slot << 11) | (func << 8) | (where & 0xfc) |
	       0x80000000;
}
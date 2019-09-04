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
struct ppc_plt_entry {int* jump; } ;
typedef  int Elf32_Addr ;

/* Variables and functions */

__attribute__((used)) static inline int entry_matches(struct ppc_plt_entry *entry, Elf32_Addr val)
{
	if (entry->jump[0] == 0x3d800000 + ((val + 0x8000) >> 16)
	    && entry->jump[1] == 0x398c0000 + (val & 0xffff))
		return 1;
	return 0;
}
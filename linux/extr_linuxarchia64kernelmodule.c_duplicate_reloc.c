#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ r_info; scalar_t__ r_addend; } ;
typedef  TYPE_1__ Elf64_Rela ;

/* Variables and functions */

__attribute__((used)) static int
duplicate_reloc (const Elf64_Rela *rela, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++) {
		if (rela[i].r_info == rela[num].r_info && rela[i].r_addend == rela[num].r_addend)
			return 1;
	}
	return 0;
}
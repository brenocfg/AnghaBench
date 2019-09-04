#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t e_shstrndx; unsigned int e_shnum; } ;
struct TYPE_4__ {int sh_name; } ;
struct TYPE_5__ {char* strtab; TYPE_1__ shdr; } ;

/* Variables and functions */
 unsigned int SHN_ABS ; 
 unsigned int SHN_COMMON ; 
 TYPE_3__ ehdr ; 
 TYPE_2__* secs ; 

__attribute__((used)) static const char *sec_name(unsigned shndx)
{
	const char *sec_strtab;
	const char *name;

	sec_strtab = secs[ehdr.e_shstrndx].strtab;
	if (shndx < ehdr.e_shnum)
		name = sec_strtab + secs[shndx].shdr.sh_name;
	else if (shndx == SHN_ABS)
		name = "ABSOLUTE";
	else if (shndx == SHN_COMMON)
		name = "COMMON";
	else
		name = "<noname>";
	return name;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ p_vaddr; } ;
typedef  TYPE_1__ Elf32_Phdr ;

/* Variables and functions */

__attribute__((used)) static int phcmp(const void *v1, const void *v2)
{
	const Elf32_Phdr *h1 = v1;
	const Elf32_Phdr *h2 = v2;

	if (h1->p_vaddr > h2->p_vaddr)
		return 1;
	else if (h1->p_vaddr < h2->p_vaddr)
		return -1;
	else
		return 0;
}
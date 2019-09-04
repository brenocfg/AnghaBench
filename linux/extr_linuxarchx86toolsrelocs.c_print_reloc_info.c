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

/* Variables and functions */
 int /*<<< orphan*/  do_reloc_info ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  walk_relocs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_reloc_info(void)
{
	printf("reloc section\treloc type\tsymbol\tsymbol section\n");
	walk_relocs(do_reloc_info);
}
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
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  walk_relocs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_reloc_info(void)
{
	printf("%16s  %10s  %16s  %40s  %16s\n",
		"reloc section",
		"offset",
		"reloc type",
		"symbol",
		"symbol section");
	walk_relocs(do_reloc_info);
}
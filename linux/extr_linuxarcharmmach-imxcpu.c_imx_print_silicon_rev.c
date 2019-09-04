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
 int IMX_CHIP_REVISION_UNKNOWN ; 
 int /*<<< orphan*/  pr_info (char*,char const*,...) ; 

void imx_print_silicon_rev(const char *cpu, int srev)
{
	if (srev == IMX_CHIP_REVISION_UNKNOWN)
		pr_info("CPU identified as %s, unknown revision\n", cpu);
	else
		pr_info("CPU identified as %s, silicon rev %d.%d\n",
				cpu, (srev >> 4) & 0xf, srev & 0xf);
}
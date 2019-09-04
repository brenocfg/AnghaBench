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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 scalar_t__ VT8500_PMSR_REG ; 
 scalar_t__ pmc_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vt8500_restart(enum reboot_mode mode, const char *cmd)
{
	if (pmc_base)
		writel(1, pmc_base + VT8500_PMSR_REG);
}
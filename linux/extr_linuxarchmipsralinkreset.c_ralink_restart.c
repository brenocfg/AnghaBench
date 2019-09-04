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
 int /*<<< orphan*/  CONFIG_PCI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTCTL_RESET_PCI ; 
 int /*<<< orphan*/  RSTCTL_RESET_SYSTEM ; 
 int /*<<< orphan*/  SYSC_REG_RESET_CTRL ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rt_sysc_m32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_sysc_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreachable () ; 

__attribute__((used)) static void ralink_restart(char *command)
{
	if (IS_ENABLED(CONFIG_PCI)) {
		rt_sysc_m32(0, RSTCTL_RESET_PCI, SYSC_REG_RESET_CTRL);
		mdelay(50);
	}

	local_irq_disable();
	rt_sysc_w32(RSTCTL_RESET_SYSTEM, SYSC_REG_RESET_CTRL);
	unreachable();
}
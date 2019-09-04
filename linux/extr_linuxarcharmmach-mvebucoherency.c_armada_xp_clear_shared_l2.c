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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CONFIG_SHARED_L2 ; 
 int /*<<< orphan*/  cpu_config_base ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armada_xp_clear_shared_l2(void)
{
	u32 reg;

	if (!cpu_config_base)
		return;

	reg = readl(cpu_config_base);
	reg &= ~CPU_CONFIG_SHARED_L2;
	writel(reg, cpu_config_base);
}
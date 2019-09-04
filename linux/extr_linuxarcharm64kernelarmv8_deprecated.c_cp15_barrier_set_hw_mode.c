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
 int /*<<< orphan*/  SCTLR_EL1_CP15BEN ; 
 int /*<<< orphan*/  sctlr_el1 ; 
 int /*<<< orphan*/  sysreg_clear_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp15_barrier_set_hw_mode(bool enable)
{
	if (enable)
		sysreg_clear_set(sctlr_el1, 0, SCTLR_EL1_CP15BEN);
	else
		sysreg_clear_set(sctlr_el1, SCTLR_EL1_CP15BEN, 0);
	return 0;
}
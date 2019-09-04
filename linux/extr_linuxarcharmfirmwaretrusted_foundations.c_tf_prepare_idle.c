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
 int /*<<< orphan*/  TF_CPU_PM ; 
 int /*<<< orphan*/  TF_CPU_PM_S1_NOFLUSH_L2 ; 
 int /*<<< orphan*/  cpu_boot_addr ; 
 int /*<<< orphan*/  tf_generic_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tf_prepare_idle(void)
{
	tf_generic_smc(TF_CPU_PM, TF_CPU_PM_S1_NOFLUSH_L2, cpu_boot_addr);

	return 0;
}
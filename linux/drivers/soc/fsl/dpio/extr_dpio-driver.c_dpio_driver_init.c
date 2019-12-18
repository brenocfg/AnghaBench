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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_unused_mask ; 
 int /*<<< orphan*/  dpaa2_dpio_driver ; 
 int fsl_mc_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpio_driver_init(void)
{
	if (!zalloc_cpumask_var(&cpus_unused_mask, GFP_KERNEL))
		return -ENOMEM;
	cpumask_copy(cpus_unused_mask, cpu_online_mask);

	return fsl_mc_driver_register(&dpaa2_dpio_driver);
}
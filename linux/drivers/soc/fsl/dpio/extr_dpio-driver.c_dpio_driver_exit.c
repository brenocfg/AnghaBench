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
 int /*<<< orphan*/  cpus_unused_mask ; 
 int /*<<< orphan*/  dpaa2_dpio_driver ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_mc_driver_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpio_driver_exit(void)
{
	free_cpumask_var(cpus_unused_mask);
	fsl_mc_driver_unregister(&dpaa2_dpio_driver);
}
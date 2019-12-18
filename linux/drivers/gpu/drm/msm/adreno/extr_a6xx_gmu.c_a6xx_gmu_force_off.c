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
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  a6xx_gmu_irq_disable (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_gmu_rpmh_off (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_hfi_stop (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_sptprac_disable (struct a6xx_gmu*) ; 

__attribute__((used)) static void a6xx_gmu_force_off(struct a6xx_gmu *gmu)
{
	/* Flush all the queues */
	a6xx_hfi_stop(gmu);

	/* Stop the interrupts */
	a6xx_gmu_irq_disable(gmu);

	/* Force off SPTP in case the GMU is managing it */
	a6xx_sptprac_disable(gmu);

	/* Make sure there are no outstanding RPMh votes */
	a6xx_gmu_rpmh_off(gmu);
}
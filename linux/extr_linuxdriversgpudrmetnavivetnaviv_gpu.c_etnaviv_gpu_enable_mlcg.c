#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int revision; scalar_t__ model; int minor_features3; int minor_features0; int minor_features1; } ;
struct etnaviv_gpu {TYPE_1__ identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GC2000 ; 
 int /*<<< orphan*/  GC4000 ; 
 int /*<<< orphan*/  VIVS_PM_MODULE_CONTROLS ; 
 int /*<<< orphan*/  VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_PA ; 
 int /*<<< orphan*/  VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_PE ; 
 int /*<<< orphan*/  VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_RA_EZ ; 
 int /*<<< orphan*/  VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_RA_HZ ; 
 int /*<<< orphan*/  VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_TX ; 
 int /*<<< orphan*/  VIVS_PM_POWER_CONTROLS ; 
 int /*<<< orphan*/  VIVS_PM_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING ; 
 int /*<<< orphan*/  VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING ; 
 int chipMinorFeatures0_HZ ; 
 int chipMinorFeatures1_DISABLE_PE_GATING ; 
 int chipMinorFeatures3_BUG_FIXES12 ; 
 scalar_t__ chipModel_GC400 ; 
 scalar_t__ chipModel_GC420 ; 
 scalar_t__ etnaviv_is_model_rev (struct etnaviv_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_gpu_enable_mlcg(struct etnaviv_gpu *gpu)
{
	u32 pmc, ppc;

	/* enable clock gating */
	ppc = gpu_read(gpu, VIVS_PM_POWER_CONTROLS);
	ppc |= VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING;

	/* Disable stall module clock gating for 4.3.0.1 and 4.3.0.2 revs */
	if (gpu->identity.revision == 0x4301 ||
	    gpu->identity.revision == 0x4302)
		ppc |= VIVS_PM_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING;

	gpu_write(gpu, VIVS_PM_POWER_CONTROLS, ppc);

	pmc = gpu_read(gpu, VIVS_PM_MODULE_CONTROLS);

	/* Disable PA clock gating for GC400+ without bugfix except for GC420 */
	if (gpu->identity.model >= chipModel_GC400 &&
	    gpu->identity.model != chipModel_GC420 &&
	    !(gpu->identity.minor_features3 & chipMinorFeatures3_BUG_FIXES12))
		pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_PA;

	/*
	 * Disable PE clock gating on revs < 5.0.0.0 when HZ is
	 * present without a bug fix.
	 */
	if (gpu->identity.revision < 0x5000 &&
	    gpu->identity.minor_features0 & chipMinorFeatures0_HZ &&
	    !(gpu->identity.minor_features1 &
	      chipMinorFeatures1_DISABLE_PE_GATING))
		pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_PE;

	if (gpu->identity.revision < 0x5422)
		pmc |= BIT(15); /* Unknown bit */

	/* Disable TX clock gating on affected core revisions. */
	if (etnaviv_is_model_rev(gpu, GC4000, 0x5222) ||
	    etnaviv_is_model_rev(gpu, GC2000, 0x5108))
		pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_TX;

	pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_RA_HZ;
	pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_RA_EZ;

	gpu_write(gpu, VIVS_PM_MODULE_CONTROLS, pmc);
}
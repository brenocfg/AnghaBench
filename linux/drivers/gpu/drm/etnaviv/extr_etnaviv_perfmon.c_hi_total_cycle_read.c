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
struct etnaviv_pm_signal {int dummy; } ;
struct etnaviv_pm_domain {int dummy; } ;
struct TYPE_2__ {scalar_t__ model; } ;
struct etnaviv_gpu {TYPE_1__ identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_HI_PROFILE_TOTAL_CYCLES ; 
 int /*<<< orphan*/  VIVS_MC_PROFILE_CYCLE_COUNTER ; 
 scalar_t__ chipModel_GC2000 ; 
 scalar_t__ chipModel_GC2100 ; 
 scalar_t__ chipModel_GC880 ; 
 int /*<<< orphan*/  gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hi_total_cycle_read(struct etnaviv_gpu *gpu,
	const struct etnaviv_pm_domain *domain,
	const struct etnaviv_pm_signal *signal)
{
	u32 reg = VIVS_HI_PROFILE_TOTAL_CYCLES;

	if (gpu->identity.model == chipModel_GC880 ||
		gpu->identity.model == chipModel_GC2000 ||
		gpu->identity.model == chipModel_GC2100)
		reg = VIVS_MC_PROFILE_CYCLE_COUNTER;

	return gpu_read(gpu, reg);
}
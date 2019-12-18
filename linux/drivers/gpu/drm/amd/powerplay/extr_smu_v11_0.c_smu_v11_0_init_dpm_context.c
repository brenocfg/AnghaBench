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
struct smu_dpm_context {scalar_t__ dpm_context_size; scalar_t__ dpm_context; } ;
struct smu_context {struct smu_dpm_context smu_dpm; } ;

/* Variables and functions */
 int EINVAL ; 
 int smu_alloc_dpm_context (struct smu_context*) ; 

__attribute__((used)) static int smu_v11_0_init_dpm_context(struct smu_context *smu)
{
	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	if (smu_dpm->dpm_context || smu_dpm->dpm_context_size != 0)
		return -EINVAL;

	return smu_alloc_dpm_context(smu);
}
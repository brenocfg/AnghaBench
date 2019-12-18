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
struct vega20_dpm_table {int dummy; } ;
struct smu_power_state {int dummy; } ;
struct smu_dpm_context {int dpm_context_size; void* dpm_request_power_state; void* dpm_current_power_state; void* golden_dpm_context; void* dpm_context; } ;
struct smu_context {struct smu_dpm_context smu_dpm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_allocate_dpm_context(struct smu_context *smu)
{
	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	if (smu_dpm->dpm_context)
		return -EINVAL;

	smu_dpm->dpm_context = kzalloc(sizeof(struct vega20_dpm_table),
				       GFP_KERNEL);
	if (!smu_dpm->dpm_context)
		return -ENOMEM;

	if (smu_dpm->golden_dpm_context)
		return -EINVAL;

	smu_dpm->golden_dpm_context = kzalloc(sizeof(struct vega20_dpm_table),
					      GFP_KERNEL);
	if (!smu_dpm->golden_dpm_context)
		return -ENOMEM;

	smu_dpm->dpm_context_size = sizeof(struct vega20_dpm_table);

	smu_dpm->dpm_current_power_state = kzalloc(sizeof(struct smu_power_state),
				       GFP_KERNEL);
	if (!smu_dpm->dpm_current_power_state)
		return -ENOMEM;

	smu_dpm->dpm_request_power_state = kzalloc(sizeof(struct smu_power_state),
				       GFP_KERNEL);
	if (!smu_dpm->dpm_request_power_state)
		return -ENOMEM;

	return 0;
}
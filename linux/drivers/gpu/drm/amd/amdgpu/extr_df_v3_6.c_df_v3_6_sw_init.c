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
struct amdgpu_device {scalar_t__* df_perfmon_config_assign_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMDGPU_MAX_DF_PERFMONS ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  dev_attr_df_cntr_avail ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void df_v3_6_sw_init(struct amdgpu_device *adev)
{
	int i, ret;

	ret = device_create_file(adev->dev, &dev_attr_df_cntr_avail);
	if (ret)
		DRM_ERROR("failed to create file for available df counters\n");

	for (i = 0; i < AMDGPU_MAX_DF_PERFMONS; i++)
		adev->df_perfmon_config_assign_mask[i] = 0;
}
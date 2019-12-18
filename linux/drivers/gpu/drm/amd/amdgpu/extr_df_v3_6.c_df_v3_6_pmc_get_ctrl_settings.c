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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int DF_V3_6_GET_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ DF_V3_6_GET_INSTANCE (int /*<<< orphan*/ ) ; 
 int DF_V3_6_GET_UNITMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 int ENXIO ; 
 int /*<<< orphan*/  df_v3_6_pmc_get_addr (struct amdgpu_device*,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int df_v3_6_pmc_get_ctrl_settings(struct amdgpu_device *adev,
					  uint64_t config,
					  uint32_t *lo_base_addr,
					  uint32_t *hi_base_addr,
					  uint32_t *lo_val,
					  uint32_t *hi_val)
{

	uint32_t eventsel, instance, unitmask;
	uint32_t instance_10, instance_5432, instance_76;

	df_v3_6_pmc_get_addr(adev, config, 1, lo_base_addr, hi_base_addr);

	if ((*lo_base_addr == 0) || (*hi_base_addr == 0)) {
		DRM_ERROR("[DF PMC] addressing not retrieved! Lo: %x, Hi: %x",
				*lo_base_addr, *hi_base_addr);
		return -ENXIO;
	}

	eventsel = DF_V3_6_GET_EVENT(config) & 0x3f;
	unitmask = DF_V3_6_GET_UNITMASK(config) & 0xf;
	instance = DF_V3_6_GET_INSTANCE(config);

	instance_10 = instance & 0x3;
	instance_5432 = (instance >> 2) & 0xf;
	instance_76 = (instance >> 6) & 0x3;

	*lo_val = (unitmask << 8) | (instance_10 << 6) | eventsel | (1 << 22);
	*hi_val = (instance_76 << 29) | instance_5432;

	DRM_DEBUG_DRIVER("config=%llx addr=%08x:%08x val=%08x:%08x",
		config, *lo_base_addr, *hi_base_addr, *lo_val, *hi_val);

	return 0;
}
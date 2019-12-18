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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ACOverdriveSupport ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int const) ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_overdrive_feature_capabilities_array(
		struct pp_hwmgr *hwmgr,
		uint8_t **pptable_info_array,
		const uint8_t *pptable_array,
		uint8_t od_feature_count)
{
	uint32_t array_size, i;
	uint8_t *table;
	bool od_supported = false;

	array_size = sizeof(uint8_t) * od_feature_count;
	table = kzalloc(array_size, GFP_KERNEL);
	if (NULL == table)
		return -ENOMEM;

	for (i = 0; i < od_feature_count; i++) {
		table[i] = le32_to_cpu(pptable_array[i]);
		if (table[i])
			od_supported = true;
	}

	*pptable_info_array = table;

	if (od_supported)
		phm_cap_set(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_ACOverdriveSupport);

	return 0;
}
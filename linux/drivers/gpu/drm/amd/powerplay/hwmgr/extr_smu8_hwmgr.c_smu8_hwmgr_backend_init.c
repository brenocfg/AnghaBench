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
struct smu8_hwmgr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hardwareActivityPerformanceLevels; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMU8_MAX_HARDWARE_POWERLEVELS ; 
 struct smu8_hwmgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu8_construct_boot_state (struct pp_hwmgr*) ; 
 int smu8_get_system_info_data (struct pp_hwmgr*) ; 
 int smu8_initialize_dpm_defaults (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_hwmgr_backend_init(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	struct smu8_hwmgr *data;

	data = kzalloc(sizeof(struct smu8_hwmgr), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	hwmgr->backend = data;

	result = smu8_initialize_dpm_defaults(hwmgr);
	if (result != 0) {
		pr_err("smu8_initialize_dpm_defaults failed\n");
		return result;
	}

	result = smu8_get_system_info_data(hwmgr);
	if (result != 0) {
		pr_err("smu8_get_system_info_data failed\n");
		return result;
	}

	smu8_construct_boot_state(hwmgr);

	hwmgr->platform_descriptor.hardwareActivityPerformanceLevels =  SMU8_MAX_HARDWARE_POWERLEVELS;

	return result;
}
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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int iceland_smu_start_smc (struct pp_hwmgr*) ; 
 int iceland_smu_upload_firmware_image (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smu7_is_smc_ram_running (struct pp_hwmgr*) ; 
 int smu7_request_smu_load_fw (struct pp_hwmgr*) ; 

__attribute__((used)) static int iceland_start_smu(struct pp_hwmgr *hwmgr)
{
	int result;

	result = iceland_smu_upload_firmware_image(hwmgr);
	if (result)
		return result;
	result = iceland_smu_start_smc(hwmgr);
	if (result)
		return result;

	if (!smu7_is_smc_ram_running(hwmgr)) {
		pr_info("smu not running, upload firmware again \n");
		result = iceland_smu_upload_firmware_image(hwmgr);
		if (result)
			return result;

		result = iceland_smu_start_smc(hwmgr);
		if (result)
			return result;
	}

	result = smu7_request_smu_load_fw(hwmgr);

	return result;
}
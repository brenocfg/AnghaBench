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
struct intel_uc_fw {int type; char const* path; int user_overridden; } ;

/* Variables and functions */
#define  INTEL_UC_FW_TYPE_GUC 129 
#define  INTEL_UC_FW_TYPE_HUC 128 
 char* __override_guc_firmware_path () ; 
 char* __override_huc_firmware_path () ; 
 scalar_t__ unlikely (char const*) ; 

__attribute__((used)) static void __uc_fw_user_override(struct intel_uc_fw *uc_fw)
{
	const char *path = NULL;

	switch (uc_fw->type) {
	case INTEL_UC_FW_TYPE_GUC:
		path = __override_guc_firmware_path();
		break;
	case INTEL_UC_FW_TYPE_HUC:
		path = __override_huc_firmware_path();
		break;
	}

	if (unlikely(path)) {
		uc_fw->path = path;
		uc_fw->user_overridden = true;
	}
}
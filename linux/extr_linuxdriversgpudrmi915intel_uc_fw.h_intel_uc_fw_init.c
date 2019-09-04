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
struct intel_uc_fw {int type; void* load_status; void* fetch_status; int /*<<< orphan*/ * path; } ;
typedef  enum intel_uc_fw_type { ____Placeholder_intel_uc_fw_type } intel_uc_fw_type ;

/* Variables and functions */
 void* INTEL_UC_FIRMWARE_NONE ; 

__attribute__((used)) static inline
void intel_uc_fw_init(struct intel_uc_fw *uc_fw, enum intel_uc_fw_type type)
{
	uc_fw->path = NULL;
	uc_fw->fetch_status = INTEL_UC_FIRMWARE_NONE;
	uc_fw->load_status = INTEL_UC_FIRMWARE_NONE;
	uc_fw->type = type;
}
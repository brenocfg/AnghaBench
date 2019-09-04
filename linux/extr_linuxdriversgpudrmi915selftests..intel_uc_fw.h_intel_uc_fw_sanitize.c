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
struct intel_uc_fw {scalar_t__ load_status; } ;

/* Variables and functions */
 scalar_t__ INTEL_UC_FIRMWARE_PENDING ; 
 scalar_t__ INTEL_UC_FIRMWARE_SUCCESS ; 

__attribute__((used)) static inline void intel_uc_fw_sanitize(struct intel_uc_fw *uc_fw)
{
	if (uc_fw->load_status == INTEL_UC_FIRMWARE_SUCCESS)
		uc_fw->load_status = INTEL_UC_FIRMWARE_PENDING;
}
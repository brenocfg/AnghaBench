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
struct intel_uc_fw {scalar_t__ status; } ;
typedef  enum intel_uc_fw_status { ____Placeholder_intel_uc_fw_status } intel_uc_fw_status ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ INTEL_UC_FIRMWARE_UNINITIALIZED ; 

__attribute__((used)) static inline enum intel_uc_fw_status
__intel_uc_fw_status(struct intel_uc_fw *uc_fw)
{
	/* shouldn't call this before checking hw/blob availability */
	GEM_BUG_ON(uc_fw->status == INTEL_UC_FIRMWARE_UNINITIALIZED);
	return uc_fw->status;
}
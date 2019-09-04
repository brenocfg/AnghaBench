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
typedef  scalar_t__ u32 ;
struct intel_uc_fw {scalar_t__ fetch_status; scalar_t__ ucode_size; scalar_t__ header_size; } ;

/* Variables and functions */
 scalar_t__ INTEL_UC_FIRMWARE_SUCCESS ; 

__attribute__((used)) static inline u32 intel_uc_fw_get_upload_size(struct intel_uc_fw *uc_fw)
{
	if (uc_fw->fetch_status != INTEL_UC_FIRMWARE_SUCCESS)
		return 0;

	return uc_fw->header_size + uc_fw->ucode_size;
}
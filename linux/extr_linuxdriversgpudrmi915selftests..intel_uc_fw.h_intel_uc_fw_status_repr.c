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
typedef  enum intel_uc_fw_status { ____Placeholder_intel_uc_fw_status } intel_uc_fw_status ;

/* Variables and functions */
#define  INTEL_UC_FIRMWARE_FAIL 131 
#define  INTEL_UC_FIRMWARE_NONE 130 
#define  INTEL_UC_FIRMWARE_PENDING 129 
#define  INTEL_UC_FIRMWARE_SUCCESS 128 

__attribute__((used)) static inline
const char *intel_uc_fw_status_repr(enum intel_uc_fw_status status)
{
	switch (status) {
	case INTEL_UC_FIRMWARE_FAIL:
		return "FAIL";
	case INTEL_UC_FIRMWARE_NONE:
		return "NONE";
	case INTEL_UC_FIRMWARE_PENDING:
		return "PENDING";
	case INTEL_UC_FIRMWARE_SUCCESS:
		return "SUCCESS";
	}
	return "<invalid>";
}
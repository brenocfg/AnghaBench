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
#define  INTEL_UC_FIRMWARE_AVAILABLE 137 
#define  INTEL_UC_FIRMWARE_DISABLED 136 
#define  INTEL_UC_FIRMWARE_ERROR 135 
#define  INTEL_UC_FIRMWARE_FAIL 134 
#define  INTEL_UC_FIRMWARE_MISSING 133 
#define  INTEL_UC_FIRMWARE_NOT_SUPPORTED 132 
#define  INTEL_UC_FIRMWARE_RUNNING 131 
#define  INTEL_UC_FIRMWARE_SELECTED 130 
#define  INTEL_UC_FIRMWARE_TRANSFERRED 129 
#define  INTEL_UC_FIRMWARE_UNINITIALIZED 128 

__attribute__((used)) static inline
const char *intel_uc_fw_status_repr(enum intel_uc_fw_status status)
{
	switch (status) {
	case INTEL_UC_FIRMWARE_NOT_SUPPORTED:
		return "N/A";
	case INTEL_UC_FIRMWARE_UNINITIALIZED:
		return "UNINITIALIZED";
	case INTEL_UC_FIRMWARE_DISABLED:
		return "DISABLED";
	case INTEL_UC_FIRMWARE_SELECTED:
		return "SELECTED";
	case INTEL_UC_FIRMWARE_MISSING:
		return "MISSING";
	case INTEL_UC_FIRMWARE_ERROR:
		return "ERROR";
	case INTEL_UC_FIRMWARE_AVAILABLE:
		return "AVAILABLE";
	case INTEL_UC_FIRMWARE_FAIL:
		return "FAIL";
	case INTEL_UC_FIRMWARE_TRANSFERRED:
		return "TRANSFERRED";
	case INTEL_UC_FIRMWARE_RUNNING:
		return "RUNNING";
	}
	return "<invalid>";
}
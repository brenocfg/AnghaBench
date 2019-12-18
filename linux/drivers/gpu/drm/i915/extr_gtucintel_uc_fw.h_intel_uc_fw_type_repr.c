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
typedef  enum intel_uc_fw_type { ____Placeholder_intel_uc_fw_type } intel_uc_fw_type ;

/* Variables and functions */
#define  INTEL_UC_FW_TYPE_GUC 129 
#define  INTEL_UC_FW_TYPE_HUC 128 

__attribute__((used)) static inline const char *intel_uc_fw_type_repr(enum intel_uc_fw_type type)
{
	switch (type) {
	case INTEL_UC_FW_TYPE_GUC:
		return "GuC";
	case INTEL_UC_FW_TYPE_HUC:
		return "HuC";
	}
	return "uC";
}
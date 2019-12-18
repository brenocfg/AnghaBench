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
struct TYPE_2__ {int enable_guc; char const* guc_firmware_path; } ;

/* Variables and functions */
 int ENABLE_GUC_LOAD_HUC ; 
 int ENABLE_GUC_SUBMISSION ; 
 TYPE_1__ i915_modparams ; 

__attribute__((used)) static const char *__override_guc_firmware_path(void)
{
	if (i915_modparams.enable_guc & (ENABLE_GUC_SUBMISSION |
					 ENABLE_GUC_LOAD_HUC))
		return i915_modparams.guc_firmware_path;
	return "";
}
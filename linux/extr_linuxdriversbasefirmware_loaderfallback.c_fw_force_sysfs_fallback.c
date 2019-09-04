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
typedef  enum fw_opt { ____Placeholder_fw_opt } fw_opt ;
struct TYPE_2__ {scalar_t__ force_sysfs_fallback; } ;

/* Variables and functions */
 int FW_OPT_USERHELPER ; 
 TYPE_1__ fw_fallback_config ; 

__attribute__((used)) static bool fw_force_sysfs_fallback(enum fw_opt opt_flags)
{
	if (fw_fallback_config.force_sysfs_fallback)
		return true;
	if (!(opt_flags & FW_OPT_USERHELPER))
		return false;
	return true;
}
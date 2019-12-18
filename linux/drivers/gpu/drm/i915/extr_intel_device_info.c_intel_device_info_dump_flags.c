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
struct intel_device_info {int dummy; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_INFO_DISPLAY_FOR_EACH_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_INFO_FOR_EACH_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_FLAG ; 

void intel_device_info_dump_flags(const struct intel_device_info *info,
				  struct drm_printer *p)
{
#define PRINT_FLAG(name) drm_printf(p, "%s: %s\n", #name, yesno(info->name));
	DEV_INFO_FOR_EACH_FLAG(PRINT_FLAG);
#undef PRINT_FLAG

#define PRINT_FLAG(name) drm_printf(p, "%s: %s\n", #name, yesno(info->display.name));
	DEV_INFO_DISPLAY_FOR_EACH_FLAG(PRINT_FLAG);
#undef PRINT_FLAG
}
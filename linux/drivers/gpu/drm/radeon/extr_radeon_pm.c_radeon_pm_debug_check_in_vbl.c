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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,char*) ; 
 int radeon_pm_in_vbl (struct radeon_device*) ; 

__attribute__((used)) static bool radeon_pm_debug_check_in_vbl(struct radeon_device *rdev, bool finish)
{
	u32 stat_crtc = 0;
	bool in_vbl = radeon_pm_in_vbl(rdev);

	if (in_vbl == false)
		DRM_DEBUG_DRIVER("not in vbl for pm change %08x at %s\n", stat_crtc,
			 finish ? "exit" : "entry");
	return in_vbl;
}
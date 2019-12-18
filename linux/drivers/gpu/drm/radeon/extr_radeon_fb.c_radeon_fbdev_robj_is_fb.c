#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* rfbdev; } ;
struct radeon_device {TYPE_3__ mode_info; } ;
struct radeon_bo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_5__ {TYPE_1__ fb; } ;

/* Variables and functions */
 struct radeon_bo* gem_to_radeon_bo (int /*<<< orphan*/ ) ; 

bool radeon_fbdev_robj_is_fb(struct radeon_device *rdev, struct radeon_bo *robj)
{
	if (!rdev->mode_info.rfbdev)
		return false;

	if (robj == gem_to_radeon_bo(rdev->mode_info.rfbdev->fb.obj[0]))
		return true;
	return false;
}
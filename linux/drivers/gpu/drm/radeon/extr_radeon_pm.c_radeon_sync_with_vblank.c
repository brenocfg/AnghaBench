#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vblank_sync; scalar_t__ active_crtcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  vblank_queue; } ;
struct radeon_device {TYPE_2__ pm; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_WAIT_VBLANK_TIMEOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_sync_with_vblank(struct radeon_device *rdev)
{
	if (rdev->pm.active_crtcs) {
		rdev->pm.vblank_sync = false;
		wait_event_timeout(
			rdev->irq.vblank_queue, rdev->pm.vblank_sync,
			msecs_to_jiffies(RADEON_WAIT_VBLANK_TIMEOUT));
	}
}
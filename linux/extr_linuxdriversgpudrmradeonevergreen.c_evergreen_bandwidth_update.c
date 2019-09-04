#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {TYPE_3__** crtcs; int /*<<< orphan*/  mode_config_initialized; } ;
struct radeon_device {int num_crtc; TYPE_2__ mode_info; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_5__ {struct drm_display_mode mode; scalar_t__ enabled; } ;
struct TYPE_7__ {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ evergreen_line_buffer_adjust (struct radeon_device*,TYPE_3__*,struct drm_display_mode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  evergreen_program_watermarks (struct radeon_device*,TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  radeon_update_display_priority (struct radeon_device*) ; 

void evergreen_bandwidth_update(struct radeon_device *rdev)
{
	struct drm_display_mode *mode0 = NULL;
	struct drm_display_mode *mode1 = NULL;
	u32 num_heads = 0, lb_size;
	int i;

	if (!rdev->mode_info.mode_config_initialized)
		return;

	radeon_update_display_priority(rdev);

	for (i = 0; i < rdev->num_crtc; i++) {
		if (rdev->mode_info.crtcs[i]->base.enabled)
			num_heads++;
	}
	for (i = 0; i < rdev->num_crtc; i += 2) {
		mode0 = &rdev->mode_info.crtcs[i]->base.mode;
		mode1 = &rdev->mode_info.crtcs[i+1]->base.mode;
		lb_size = evergreen_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i], mode0, mode1);
		evergreen_program_watermarks(rdev, rdev->mode_info.crtcs[i], lb_size, num_heads);
		lb_size = evergreen_line_buffer_adjust(rdev, rdev->mode_info.crtcs[i+1], mode1, mode0);
		evergreen_program_watermarks(rdev, rdev->mode_info.crtcs[i+1], lb_size, num_heads);
	}
}
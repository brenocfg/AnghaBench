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
struct amdgpu_dm_backlight_caps {int caps_valid; int /*<<< orphan*/  max_input_signal; int /*<<< orphan*/  min_input_signal; } ;
struct amdgpu_device {TYPE_2__* atif; } ;
struct TYPE_3__ {int caps_valid; int /*<<< orphan*/  max_input_signal; int /*<<< orphan*/  min_input_signal; } ;
struct TYPE_4__ {TYPE_1__ backlight_caps; } ;

/* Variables and functions */

void amdgpu_acpi_get_backlight_caps(struct amdgpu_device *adev,
		struct amdgpu_dm_backlight_caps *caps)
{
	if (!adev->atif) {
		caps->caps_valid = false;
		return;
	}
	caps->caps_valid = adev->atif->backlight_caps.caps_valid;
	caps->min_input_signal = adev->atif->backlight_caps.min_input_signal;
	caps->max_input_signal = adev->atif->backlight_caps.max_input_signal;
}
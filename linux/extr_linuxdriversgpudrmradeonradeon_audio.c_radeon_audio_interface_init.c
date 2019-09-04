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
struct TYPE_2__ {int /*<<< orphan*/ * dp_funcs; int /*<<< orphan*/ * hdmi_funcs; int /*<<< orphan*/ * funcs; } ;
struct radeon_device {TYPE_1__ audio; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE32 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  dce32_dp_funcs ; 
 int /*<<< orphan*/  dce32_funcs ; 
 int /*<<< orphan*/  dce32_hdmi_funcs ; 
 int /*<<< orphan*/  dce4_dp_funcs ; 
 int /*<<< orphan*/  dce4_funcs ; 
 int /*<<< orphan*/  dce4_hdmi_funcs ; 
 int /*<<< orphan*/  dce6_dp_funcs ; 
 int /*<<< orphan*/  dce6_funcs ; 
 int /*<<< orphan*/  dce6_hdmi_funcs ; 
 int /*<<< orphan*/  r600_funcs ; 
 int /*<<< orphan*/  r600_hdmi_funcs ; 

__attribute__((used)) static void radeon_audio_interface_init(struct radeon_device *rdev)
{
	if (ASIC_IS_DCE6(rdev)) {
		rdev->audio.funcs = &dce6_funcs;
		rdev->audio.hdmi_funcs = &dce6_hdmi_funcs;
		rdev->audio.dp_funcs = &dce6_dp_funcs;
	} else if (ASIC_IS_DCE4(rdev)) {
		rdev->audio.funcs = &dce4_funcs;
		rdev->audio.hdmi_funcs = &dce4_hdmi_funcs;
		rdev->audio.dp_funcs = &dce4_dp_funcs;
	} else if (ASIC_IS_DCE32(rdev)) {
		rdev->audio.funcs = &dce32_funcs;
		rdev->audio.hdmi_funcs = &dce32_hdmi_funcs;
		rdev->audio.dp_funcs = &dce32_dp_funcs;
	} else {
		rdev->audio.funcs = &r600_funcs;
		rdev->audio.hdmi_funcs = &r600_hdmi_funcs;
		rdev->audio.dp_funcs = 0;
	}
}
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
struct TYPE_3__ {int num_pins; struct amdgpu_audio_pin* pin; } ;
struct TYPE_4__ {TYPE_1__ audio; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;
struct amdgpu_audio_pin {scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  dce_v6_0_audio_get_connected_pins (struct amdgpu_device*) ; 

__attribute__((used)) static struct amdgpu_audio_pin *dce_v6_0_audio_get_pin(struct amdgpu_device *adev)
{
	int i;

	dce_v6_0_audio_get_connected_pins(adev);

	for (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		if (adev->mode_info.audio.pin[i].connected)
			return &adev->mode_info.audio.pin[i];
	}
	DRM_ERROR("No connected audio pins found!\n");
	return NULL;
}
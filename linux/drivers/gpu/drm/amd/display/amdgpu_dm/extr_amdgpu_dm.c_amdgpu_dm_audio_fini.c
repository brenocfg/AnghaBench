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
struct TYPE_5__ {int enabled; } ;
struct TYPE_6__ {TYPE_2__ audio; } ;
struct TYPE_4__ {int audio_registered; } ;
struct amdgpu_device {TYPE_3__ mode_info; TYPE_1__ dm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_audio ; 
 int /*<<< orphan*/  amdgpu_dm_audio_component_bind_ops ; 
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_dm_audio_fini(struct amdgpu_device *adev)
{
	if (!amdgpu_audio)
		return;

	if (!adev->mode_info.audio.enabled)
		return;

	if (adev->dm.audio_registered) {
		component_del(adev->dev, &amdgpu_dm_audio_component_bind_ops);
		adev->dm.audio_registered = false;
	}

	/* TODO: Disable audio? */

	adev->mode_info.audio.enabled = false;
}
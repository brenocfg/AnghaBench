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
struct drm_audio_component {TYPE_2__* audio_ops; } ;
struct TYPE_3__ {struct drm_audio_component* audio_component; } ;
struct amdgpu_device {TYPE_1__ dm; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_ptr; int /*<<< orphan*/  (* pin_eld_notify ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

void amdgpu_dm_audio_eld_notify(struct amdgpu_device *adev, int pin)
{
	struct drm_audio_component *acomp = adev->dm.audio_component;

	if (acomp && acomp->audio_ops && acomp->audio_ops->pin_eld_notify) {
		DRM_DEBUG_KMS("Notify ELD: %d\n", pin);

		acomp->audio_ops->pin_eld_notify(acomp->audio_ops->audio_ptr,
						 pin, -1);
	}
}
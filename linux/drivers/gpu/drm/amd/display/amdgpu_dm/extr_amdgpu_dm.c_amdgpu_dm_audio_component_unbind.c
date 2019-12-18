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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_audio_component {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * audio_component; } ;
struct amdgpu_device {TYPE_1__ dm; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void amdgpu_dm_audio_component_unbind(struct device *kdev,
					  struct device *hda_kdev, void *data)
{
	struct drm_device *dev = dev_get_drvdata(kdev);
	struct amdgpu_device *adev = dev->dev_private;
	struct drm_audio_component *acomp = data;

	acomp->ops = NULL;
	acomp->dev = NULL;
	adev->dm.audio_component = NULL;
}
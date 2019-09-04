#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  aper_base; } ;
struct TYPE_5__ {int mode_config_initialized; } ;
struct amdgpu_device {TYPE_4__ gmc; TYPE_3__* ddev; TYPE_1__ mode_info; } ;
struct TYPE_6__ {int max_width; int max_height; int preferred_depth; int prefer_shadow; int async_page_flip; int /*<<< orphan*/  fb_base; int /*<<< orphan*/ * helper_private; void* funcs; } ;
struct TYPE_7__ {TYPE_2__ mode_config; } ;

/* Variables and functions */
 int amdgpu_display_modeset_create_props (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dm_mode_config_helperfuncs ; 
 int /*<<< orphan*/  amdgpu_dm_mode_funcs ; 

__attribute__((used)) static int amdgpu_dm_mode_config_init(struct amdgpu_device *adev)
{
	int r;

	adev->mode_info.mode_config_initialized = true;

	adev->ddev->mode_config.funcs = (void *)&amdgpu_dm_mode_funcs;
	adev->ddev->mode_config.helper_private = &amdgpu_dm_mode_config_helperfuncs;

	adev->ddev->mode_config.max_width = 16384;
	adev->ddev->mode_config.max_height = 16384;

	adev->ddev->mode_config.preferred_depth = 24;
	adev->ddev->mode_config.prefer_shadow = 1;
	/* indicate support of immediate flip */
	adev->ddev->mode_config.async_page_flip = true;

	adev->ddev->mode_config.fb_base = adev->gmc.aper_base;

	r = amdgpu_display_modeset_create_props(adev);
	if (r)
		return r;

	return 0;
}
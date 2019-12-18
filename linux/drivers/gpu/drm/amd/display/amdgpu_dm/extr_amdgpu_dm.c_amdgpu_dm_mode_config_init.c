#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dm_atomic_state {int /*<<< orphan*/  base; int /*<<< orphan*/  context; } ;
struct TYPE_9__ {int /*<<< orphan*/  atomic_obj; int /*<<< orphan*/  dc; } ;
struct TYPE_8__ {int /*<<< orphan*/  aper_base; } ;
struct TYPE_6__ {int mode_config_initialized; } ;
struct amdgpu_device {TYPE_4__ dm; TYPE_5__* ddev; TYPE_3__ gmc; TYPE_1__ mode_info; } ;
struct TYPE_7__ {int max_width; int max_height; int preferred_depth; int prefer_shadow; int async_page_flip; int /*<<< orphan*/  fb_base; int /*<<< orphan*/ * helper_private; void* funcs; } ;
struct TYPE_10__ {TYPE_2__ mode_config; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amdgpu_display_modeset_create_props (struct amdgpu_device*) ; 
 int amdgpu_dm_audio_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dm_mode_config_helperfuncs ; 
 int /*<<< orphan*/  amdgpu_dm_mode_funcs ; 
 int /*<<< orphan*/  dc_create_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_resource_state_copy_construct_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_atomic_state_funcs ; 
 int /*<<< orphan*/  drm_atomic_private_obj_init (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_atomic_state*) ; 
 struct dm_atomic_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_dm_mode_config_init(struct amdgpu_device *adev)
{
	struct dm_atomic_state *state;
	int r;

	adev->mode_info.mode_config_initialized = true;

	adev->ddev->mode_config.funcs = (void *)&amdgpu_dm_mode_funcs;
	adev->ddev->mode_config.helper_private = &amdgpu_dm_mode_config_helperfuncs;

	adev->ddev->mode_config.max_width = 16384;
	adev->ddev->mode_config.max_height = 16384;

	adev->ddev->mode_config.preferred_depth = 24;
	adev->ddev->mode_config.prefer_shadow = 1;
	/* indicates support for immediate flip */
	adev->ddev->mode_config.async_page_flip = true;

	adev->ddev->mode_config.fb_base = adev->gmc.aper_base;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	state->context = dc_create_state(adev->dm.dc);
	if (!state->context) {
		kfree(state);
		return -ENOMEM;
	}

	dc_resource_state_copy_construct_current(adev->dm.dc, state->context);

	drm_atomic_private_obj_init(adev->ddev,
				    &adev->dm.atomic_obj,
				    &state->base,
				    &dm_atomic_state_funcs);

	r = amdgpu_display_modeset_create_props(adev);
	if (r)
		return r;

	r = amdgpu_dm_audio_init(adev);
	if (r)
		return r;

	return 0;
}
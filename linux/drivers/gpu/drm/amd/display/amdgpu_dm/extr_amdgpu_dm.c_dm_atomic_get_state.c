#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_private_state {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_atomic_state {struct drm_device* dev; } ;
struct dm_atomic_state {int dummy; } ;
struct amdgpu_display_manager {int /*<<< orphan*/  atomic_obj; } ;
struct amdgpu_device {struct amdgpu_display_manager dm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_private_state*) ; 
 int PTR_ERR (struct drm_private_state*) ; 
 struct drm_private_state* drm_atomic_get_private_obj_state (struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 struct dm_atomic_state* to_dm_atomic_state (struct drm_private_state*) ; 

__attribute__((used)) static int dm_atomic_get_state(struct drm_atomic_state *state,
			       struct dm_atomic_state **dm_state)
{
	struct drm_device *dev = state->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_display_manager *dm = &adev->dm;
	struct drm_private_state *priv_state;

	if (*dm_state)
		return 0;

	priv_state = drm_atomic_get_private_obj_state(state, &dm->atomic_obj);
	if (IS_ERR(priv_state))
		return PTR_ERR(priv_state);

	*dm_state = to_dm_atomic_state(priv_state);

	return 0;
}
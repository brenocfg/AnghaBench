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
struct TYPE_2__ {int /*<<< orphan*/  num_total_plane; int /*<<< orphan*/  num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_atomic_state {int allow_modeset; struct drm_device* dev; void* planes; void* crtcs; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,struct drm_atomic_state*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_atomic_state_default_release (struct drm_atomic_state*) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

int
drm_atomic_state_init(struct drm_device *dev, struct drm_atomic_state *state)
{
	kref_init(&state->ref);

	/* TODO legacy paths should maybe do a better job about
	 * setting this appropriately?
	 */
	state->allow_modeset = true;

	state->crtcs = kcalloc(dev->mode_config.num_crtc,
			       sizeof(*state->crtcs), GFP_KERNEL);
	if (!state->crtcs)
		goto fail;
	state->planes = kcalloc(dev->mode_config.num_total_plane,
				sizeof(*state->planes), GFP_KERNEL);
	if (!state->planes)
		goto fail;

	state->dev = dev;

	DRM_DEBUG_ATOMIC("Allocated atomic state %p\n", state);

	return 0;
fail:
	drm_atomic_state_default_release(state);
	return -ENOMEM;
}
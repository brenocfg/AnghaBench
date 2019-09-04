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
struct drm_plane_state {scalar_t__ crtc_w; scalar_t__ crtc_h; scalar_t__ src_w; scalar_t__ src_h; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_2__ {scalar_t__ crtc_w; scalar_t__ crtc_h; scalar_t__ src_w; scalar_t__ src_h; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vc4_plane_atomic_async_check(struct drm_plane *plane,
					struct drm_plane_state *state)
{
	/* No configuring new scaling in the fast path. */
	if (plane->state->crtc_w != state->crtc_w ||
	    plane->state->crtc_h != state->crtc_h ||
	    plane->state->src_w != state->src_w ||
	    plane->state->src_h != state->src_h)
		return -EINVAL;

	return 0;
}
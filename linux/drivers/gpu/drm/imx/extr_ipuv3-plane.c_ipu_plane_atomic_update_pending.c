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
struct ipu_plane_state {scalar_t__ use_pre; } ;
struct ipu_plane {int /*<<< orphan*/  ipu_ch; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {struct drm_plane_state* state; } ;

/* Variables and functions */
 int ipu_prg_channel_configure_pending (int /*<<< orphan*/ ) ; 
 struct ipu_plane* to_ipu_plane (struct drm_plane*) ; 
 struct ipu_plane_state* to_ipu_plane_state (struct drm_plane_state*) ; 

bool ipu_plane_atomic_update_pending(struct drm_plane *plane)
{
	struct ipu_plane *ipu_plane = to_ipu_plane(plane);
	struct drm_plane_state *state = plane->state;
	struct ipu_plane_state *ipu_state = to_ipu_plane_state(state);

	/* disabled crtcs must not block the update */
	if (!state->crtc)
		return false;

	if (ipu_state->use_pre)
		return ipu_prg_channel_configure_pending(ipu_plane->ipu_ch);

	/*
	 * Pretend no update is pending in the non-PRE/PRG case. For this to
	 * happen, an atomic update would have to be deferred until after the
	 * start of the next frame and simultaneously interrupt latency would
	 * have to be high enough to let the atomic update finish and issue an
	 * event before the previous end of frame interrupt handler can be
	 * executed.
	 */
	return false;
}
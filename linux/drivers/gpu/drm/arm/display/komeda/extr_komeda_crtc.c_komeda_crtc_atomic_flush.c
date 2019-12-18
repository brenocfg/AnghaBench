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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ drm_atomic_crtc_needs_modeset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_crtc_do_flush (struct drm_crtc*,struct drm_crtc_state*) ; 

__attribute__((used)) static void
komeda_crtc_atomic_flush(struct drm_crtc *crtc,
			 struct drm_crtc_state *old)
{
	/* commit with modeset will be handled in enable/disable */
	if (drm_atomic_crtc_needs_modeset(crtc->state))
		return;

	komeda_crtc_do_flush(crtc, old);
}
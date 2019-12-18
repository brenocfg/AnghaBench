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
struct komeda_crtc_state {int dummy; } ;
struct komeda_crtc {int /*<<< orphan*/  master; int /*<<< orphan*/  slave; } ;
struct drm_crtc_state {scalar_t__ active; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 scalar_t__ drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 int komeda_build_display_data_flow (struct komeda_crtc*,struct komeda_crtc_state*) ; 
 int /*<<< orphan*/  komeda_crtc_update_clock_ratio (struct komeda_crtc_state*) ; 
 int komeda_release_unclaimed_resources (int /*<<< orphan*/ ,struct komeda_crtc_state*) ; 
 struct komeda_crtc* to_kcrtc (struct drm_crtc*) ; 
 struct komeda_crtc_state* to_kcrtc_st (struct drm_crtc_state*) ; 

__attribute__((used)) static int
komeda_crtc_atomic_check(struct drm_crtc *crtc,
			 struct drm_crtc_state *state)
{
	struct komeda_crtc *kcrtc = to_kcrtc(crtc);
	struct komeda_crtc_state *kcrtc_st = to_kcrtc_st(state);
	int err;

	if (drm_atomic_crtc_needs_modeset(state))
		komeda_crtc_update_clock_ratio(kcrtc_st);

	if (state->active) {
		err = komeda_build_display_data_flow(kcrtc, kcrtc_st);
		if (err)
			return err;
	}

	/* release unclaimed pipeline resources */
	err = komeda_release_unclaimed_resources(kcrtc->slave, kcrtc_st);
	if (err)
		return err;

	err = komeda_release_unclaimed_resources(kcrtc->master, kcrtc_st);
	if (err)
		return err;

	return 0;
}
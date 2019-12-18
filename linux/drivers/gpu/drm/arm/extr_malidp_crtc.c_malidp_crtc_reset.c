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
struct malidp_crtc_state {int /*<<< orphan*/  base; } ;
struct drm_crtc {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_reset (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 struct malidp_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_crtc_destroy_state (struct drm_crtc*,scalar_t__) ; 

__attribute__((used)) static void malidp_crtc_reset(struct drm_crtc *crtc)
{
	struct malidp_crtc_state *state =
		kzalloc(sizeof(*state), GFP_KERNEL);

	if (crtc->state)
		malidp_crtc_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &state->base);
}
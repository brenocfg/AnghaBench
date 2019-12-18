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
struct atmel_hlcdc_crtc_state {struct drm_crtc_state base; int /*<<< orphan*/  output_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct atmel_hlcdc_crtc_state* drm_crtc_state_to_atmel_hlcdc_crtc_state (int /*<<< orphan*/ ) ; 
 struct atmel_hlcdc_crtc_state* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_state *
atmel_hlcdc_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct atmel_hlcdc_crtc_state *state, *cur;

	if (WARN_ON(!crtc->state))
		return NULL;

	state = kmalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;
	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	cur = drm_crtc_state_to_atmel_hlcdc_crtc_state(crtc->state);
	state->output_mode = cur->output_mode;

	return &state->base;
}
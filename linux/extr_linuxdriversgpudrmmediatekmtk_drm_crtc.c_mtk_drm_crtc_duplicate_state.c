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
struct drm_crtc_state {struct drm_crtc* crtc; } ;
struct mtk_crtc_state {struct drm_crtc_state base; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct mtk_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_state *mtk_drm_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct mtk_crtc_state *state;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	WARN_ON(state->base.crtc != crtc);
	state->base.crtc = crtc;

	return &state->base;
}
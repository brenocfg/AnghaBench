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
struct drm_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; } ;
struct dpu_crtc_state {int dummy; } ;
struct dpu_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  kfree (struct dpu_crtc_state*) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 struct dpu_crtc_state* to_dpu_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void dpu_crtc_destroy_state(struct drm_crtc *crtc,
		struct drm_crtc_state *state)
{
	struct dpu_crtc *dpu_crtc;
	struct dpu_crtc_state *cstate;

	if (!crtc || !state) {
		DPU_ERROR("invalid argument(s)\n");
		return;
	}

	dpu_crtc = to_dpu_crtc(crtc);
	cstate = to_dpu_crtc_state(state);

	DPU_DEBUG("crtc%d\n", crtc->base.id);

	__drm_atomic_helper_crtc_destroy_state(state);

	kfree(cstate);
}
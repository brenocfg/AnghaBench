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
struct drm_crtc {TYPE_1__* state; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct drm_crtc* crtc; } ;
struct dpu_crtc_state {TYPE_1__ base; int /*<<< orphan*/  rp; } ;
struct dpu_crtc {int /*<<< orphan*/  rp_head; int /*<<< orphan*/  rp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _dpu_crtc_rp_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dpu_crtc_set_suspend (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  dpu_crtc_destroy_state (struct drm_crtc*,TYPE_1__*) ; 
 scalar_t__ dpu_kms_is_suspend_state (int /*<<< orphan*/ ) ; 
 struct dpu_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dpu_crtc_reset(struct drm_crtc *crtc)
{
	struct dpu_crtc *dpu_crtc;
	struct dpu_crtc_state *cstate;

	if (!crtc) {
		DPU_ERROR("invalid crtc\n");
		return;
	}

	/* revert suspend actions, if necessary */
	if (dpu_kms_is_suspend_state(crtc->dev))
		_dpu_crtc_set_suspend(crtc, false);

	/* remove previous state, if present */
	if (crtc->state) {
		dpu_crtc_destroy_state(crtc, crtc->state);
		crtc->state = 0;
	}

	dpu_crtc = to_dpu_crtc(crtc);
	cstate = kzalloc(sizeof(*cstate), GFP_KERNEL);
	if (!cstate) {
		DPU_ERROR("failed to allocate state\n");
		return;
	}

	_dpu_crtc_rp_reset(&cstate->rp, &dpu_crtc->rp_lock,
			&dpu_crtc->rp_head);

	cstate->base.crtc = crtc;
	crtc->state = &cstate->base;
}
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
struct drm_encoder_helper_funcs {int /*<<< orphan*/  (* commit ) (struct drm_encoder*) ;} ;
struct drm_encoder {struct drm_crtc* crtc; struct drm_encoder_helper_funcs* helper_private; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (struct drm_crtc*) ; 
 int /*<<< orphan*/  dpu_crtc_commit_kickoff (struct drm_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_kms_enc_enable (int /*<<< orphan*/ ) ; 

void dpu_kms_encoder_enable(struct drm_encoder *encoder)
{
	const struct drm_encoder_helper_funcs *funcs = encoder->helper_private;
	struct drm_crtc *crtc = encoder->crtc;

	/* Forward this enable call to the commit hook */
	if (funcs && funcs->commit)
		funcs->commit(encoder);

	if (crtc && crtc->state->active) {
		trace_dpu_kms_enc_enable(DRMID(crtc));
		dpu_crtc_commit_kickoff(crtc);
	}
}
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
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {size_t pipe; } ;
struct intel_bw_state {int /*<<< orphan*/ * num_active_planes; int /*<<< orphan*/ * data_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_bw_crtc_data_rate (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_bw_crtc_num_active_planes (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  pipe_name (size_t) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

void intel_bw_crtc_update(struct intel_bw_state *bw_state,
			  const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);

	bw_state->data_rate[crtc->pipe] =
		intel_bw_crtc_data_rate(crtc_state);
	bw_state->num_active_planes[crtc->pipe] =
		intel_bw_crtc_num_active_planes(crtc_state);

	DRM_DEBUG_KMS("pipe %c data rate %u num active planes %u\n",
		      pipe_name(crtc->pipe),
		      bw_state->data_rate[crtc->pipe],
		      bw_state->num_active_planes[crtc->pipe]);
}
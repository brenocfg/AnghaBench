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
struct mtk_crtc_state {int pending_config; int /*<<< orphan*/  pending_vrefresh; int /*<<< orphan*/  pending_height; int /*<<< orphan*/  pending_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_crtc {TYPE_1__ mode; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 struct mtk_crtc_state* to_mtk_crtc_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mtk_drm_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct mtk_crtc_state *state = to_mtk_crtc_state(crtc->state);

	state->pending_width = crtc->mode.hdisplay;
	state->pending_height = crtc->mode.vdisplay;
	state->pending_vrefresh = crtc->mode.vrefresh;
	wmb();	/* Make sure the above parameters are set before update */
	state->pending_config = true;
}
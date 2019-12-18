#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__** crtcs; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct drm_display_mode {int hdisplay; int /*<<< orphan*/  crtc_hdisplay; } ;
struct TYPE_3__ {void* lb_vblank_lead_lines; } ;

/* Variables and functions */
 int C_006520_DC_LB_MEMORY_SPLIT ; 
 int C_006520_DC_LB_MEMORY_SPLIT_MODE ; 
 void* DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_006520_DC_LB_MEMORY_SPLIT ; 
 int V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF ; 
 int V_006520_DC_LB_MEMORY_SPLIT_D1_1Q_D2_3Q ; 
 int V_006520_DC_LB_MEMORY_SPLIT_D1_3Q_D2_1Q ; 
 int V_006520_DC_LB_MEMORY_SPLIT_D1_ONLY ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void rs690_line_buffer_adjust(struct radeon_device *rdev,
			      struct drm_display_mode *mode1,
			      struct drm_display_mode *mode2)
{
	u32 tmp;

	/* Guess line buffer size to be 8192 pixels */
	u32 lb_size = 8192;

	/*
	 * Line Buffer Setup
	 * There is a single line buffer shared by both display controllers.
	 * R_006520_DC_LB_MEMORY_SPLIT controls how that line buffer is shared between
	 * the display controllers.  The paritioning can either be done
	 * manually or via one of four preset allocations specified in bits 1:0:
	 *  0 - line buffer is divided in half and shared between crtc
	 *  1 - D1 gets 3/4 of the line buffer, D2 gets 1/4
	 *  2 - D1 gets the whole buffer
	 *  3 - D1 gets 1/4 of the line buffer, D2 gets 3/4
	 * Setting bit 2 of R_006520_DC_LB_MEMORY_SPLIT controls switches to manual
	 * allocation mode. In manual allocation mode, D1 always starts at 0,
	 * D1 end/2 is specified in bits 14:4; D2 allocation follows D1.
	 */
	tmp = RREG32(R_006520_DC_LB_MEMORY_SPLIT) & C_006520_DC_LB_MEMORY_SPLIT;
	tmp &= ~C_006520_DC_LB_MEMORY_SPLIT_MODE;
	/* auto */
	if (mode1 && mode2) {
		if (mode1->hdisplay > mode2->hdisplay) {
			if (mode1->hdisplay > 2560)
				tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1_3Q_D2_1Q;
			else
				tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF;
		} else if (mode2->hdisplay > mode1->hdisplay) {
			if (mode2->hdisplay > 2560)
				tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1_1Q_D2_3Q;
			else
				tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF;
		} else
			tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF;
	} else if (mode1) {
		tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1_ONLY;
	} else if (mode2) {
		tmp |= V_006520_DC_LB_MEMORY_SPLIT_D1_1Q_D2_3Q;
	}
	WREG32(R_006520_DC_LB_MEMORY_SPLIT, tmp);

	/* Save number of lines the linebuffer leads before the scanout */
	if (mode1)
		rdev->mode_info.crtcs[0]->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode1->crtc_hdisplay);

	if (mode2)
		rdev->mode_info.crtcs[1]->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode2->crtc_hdisplay);
}
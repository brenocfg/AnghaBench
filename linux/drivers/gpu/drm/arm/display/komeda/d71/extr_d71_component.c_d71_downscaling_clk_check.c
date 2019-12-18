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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct komeda_pipeline {int dummy; } ;
struct komeda_data_flow_cfg {int in_w; int in_h; int out_h; } ;
struct drm_display_mode {unsigned long hdisplay; int htotal; int crtc_clock; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int d71_downscaling_clk_check(struct komeda_pipeline *pipe,
				     struct drm_display_mode *mode,
				     unsigned long aclk_rate,
				     struct komeda_data_flow_cfg *dflow)
{
	u32 h_in = dflow->in_w;
	u32 v_in = dflow->in_h;
	u32 v_out = dflow->out_h;
	u64 fraction, denominator;

	/* D71 downscaling must satisfy the following equation
	 *
	 *   ACLK                   h_in * v_in
	 * ------- >= ---------------------------------------------
	 *  PXLCLK     (h_total - (1 + 2 * v_in / v_out)) * v_out
	 *
	 * In only horizontal downscaling situation, the right side should be
	 * multiplied by (h_total - 3) / (h_active - 3), then equation becomes
	 *
	 *   ACLK          h_in
	 * ------- >= ----------------
	 *  PXLCLK     (h_active - 3)
	 *
	 * To avoid precision lost the equation 1 will be convert to:
	 *
	 *   ACLK             h_in * v_in
	 * ------- >= -----------------------------------
	 *  PXLCLK     (h_total -1 ) * v_out -  2 * v_in
	 */
	if (v_in == v_out) {
		fraction = h_in;
		denominator = mode->hdisplay - 3;
	} else {
		fraction = h_in * v_in;
		denominator = (mode->htotal - 1) * v_out -  2 * v_in;
	}

	return aclk_rate * denominator >= mode->crtc_clock * 1000 * fraction ?
	       0 : -EINVAL;
}
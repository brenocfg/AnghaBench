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
typedef  int u32 ;
struct tv_mode {int hsync_end; int htotal; int hburst_start; int hburst_len; int hblank_start; int hblank_end; int nbr_end; int vi_end_f1; int vi_end_f2; int vsync_len; int vsync_start_f1; int vsync_start_f2; int veq_len; int veq_start_f1; int veq_start_f2; int vburst_start_f1; int vburst_end_f1; int vburst_start_f2; int vburst_end_f2; int vburst_start_f3; int vburst_end_f3; int vburst_start_f4; int vburst_end_f4; scalar_t__ veq_ena; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int TV_BURST_ENA ; 
 int TV_EQUAL_ENA ; 
 int TV_HBLANK_END_SHIFT ; 
 int TV_HBLANK_START_SHIFT ; 
 int TV_HBURST_LEN_SHIFT ; 
 int TV_HSYNC_END_SHIFT ; 
 int TV_HTOTAL_SHIFT ; 
 int /*<<< orphan*/  TV_H_CTL_1 ; 
 int /*<<< orphan*/  TV_H_CTL_2 ; 
 int /*<<< orphan*/  TV_H_CTL_3 ; 
 int TV_NBR_END_SHIFT ; 
 int TV_VBURST_END_F1_SHIFT ; 
 int TV_VBURST_END_F2_SHIFT ; 
 int TV_VBURST_END_F3_SHIFT ; 
 int TV_VBURST_END_F4_SHIFT ; 
 int TV_VBURST_START_F1_SHIFT ; 
 int TV_VBURST_START_F2_SHIFT ; 
 int TV_VBURST_START_F3_SHIFT ; 
 int TV_VBURST_START_F4_SHIFT ; 
 int TV_VEQ_LEN_SHIFT ; 
 int TV_VEQ_START_F1_SHIFT ; 
 int TV_VEQ_START_F2_SHIFT ; 
 int TV_VI_END_F1_SHIFT ; 
 int TV_VI_END_F2_SHIFT ; 
 int TV_VSYNC_LEN_SHIFT ; 
 int TV_VSYNC_START_F1_SHIFT ; 
 int TV_VSYNC_START_F2_SHIFT ; 
 int /*<<< orphan*/  TV_V_CTL_1 ; 
 int /*<<< orphan*/  TV_V_CTL_2 ; 
 int /*<<< orphan*/  TV_V_CTL_3 ; 
 int /*<<< orphan*/  TV_V_CTL_4 ; 
 int /*<<< orphan*/  TV_V_CTL_5 ; 
 int /*<<< orphan*/  TV_V_CTL_6 ; 
 int /*<<< orphan*/  TV_V_CTL_7 ; 

__attribute__((used)) static void
set_tv_mode_timings(struct drm_i915_private *dev_priv,
		    const struct tv_mode *tv_mode,
		    bool burst_ena)
{
	u32 hctl1, hctl2, hctl3;
	u32 vctl1, vctl2, vctl3, vctl4, vctl5, vctl6, vctl7;

	hctl1 = (tv_mode->hsync_end << TV_HSYNC_END_SHIFT) |
		(tv_mode->htotal << TV_HTOTAL_SHIFT);

	hctl2 = (tv_mode->hburst_start << 16) |
		(tv_mode->hburst_len << TV_HBURST_LEN_SHIFT);

	if (burst_ena)
		hctl2 |= TV_BURST_ENA;

	hctl3 = (tv_mode->hblank_start << TV_HBLANK_START_SHIFT) |
		(tv_mode->hblank_end << TV_HBLANK_END_SHIFT);

	vctl1 = (tv_mode->nbr_end << TV_NBR_END_SHIFT) |
		(tv_mode->vi_end_f1 << TV_VI_END_F1_SHIFT) |
		(tv_mode->vi_end_f2 << TV_VI_END_F2_SHIFT);

	vctl2 = (tv_mode->vsync_len << TV_VSYNC_LEN_SHIFT) |
		(tv_mode->vsync_start_f1 << TV_VSYNC_START_F1_SHIFT) |
		(tv_mode->vsync_start_f2 << TV_VSYNC_START_F2_SHIFT);

	vctl3 = (tv_mode->veq_len << TV_VEQ_LEN_SHIFT) |
		(tv_mode->veq_start_f1 << TV_VEQ_START_F1_SHIFT) |
		(tv_mode->veq_start_f2 << TV_VEQ_START_F2_SHIFT);

	if (tv_mode->veq_ena)
		vctl3 |= TV_EQUAL_ENA;

	vctl4 = (tv_mode->vburst_start_f1 << TV_VBURST_START_F1_SHIFT) |
		(tv_mode->vburst_end_f1 << TV_VBURST_END_F1_SHIFT);

	vctl5 = (tv_mode->vburst_start_f2 << TV_VBURST_START_F2_SHIFT) |
		(tv_mode->vburst_end_f2 << TV_VBURST_END_F2_SHIFT);

	vctl6 = (tv_mode->vburst_start_f3 << TV_VBURST_START_F3_SHIFT) |
		(tv_mode->vburst_end_f3 << TV_VBURST_END_F3_SHIFT);

	vctl7 = (tv_mode->vburst_start_f4 << TV_VBURST_START_F4_SHIFT) |
		(tv_mode->vburst_end_f4 << TV_VBURST_END_F4_SHIFT);

	I915_WRITE(TV_H_CTL_1, hctl1);
	I915_WRITE(TV_H_CTL_2, hctl2);
	I915_WRITE(TV_H_CTL_3, hctl3);
	I915_WRITE(TV_V_CTL_1, vctl1);
	I915_WRITE(TV_V_CTL_2, vctl2);
	I915_WRITE(TV_V_CTL_3, vctl3);
	I915_WRITE(TV_V_CTL_4, vctl4);
	I915_WRITE(TV_V_CTL_5, vctl5);
	I915_WRITE(TV_V_CTL_6, vctl6);
	I915_WRITE(TV_V_CTL_7, vctl7);
}
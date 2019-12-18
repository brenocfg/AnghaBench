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
struct mtk_hdmi {int dummy; } ;
struct drm_display_mode {int flags; int clock; int vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG2_MHL_DE_SEL ; 
 int /*<<< orphan*/  CFG4_MHL_MODE ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  GRL_CFG2 ; 
 int /*<<< orphan*/  GRL_CFG4 ; 
 int /*<<< orphan*/  mtk_hdmi_clear_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_set_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_msic_setting(struct mtk_hdmi *hdmi,
				     struct drm_display_mode *mode)
{
	mtk_hdmi_clear_bits(hdmi, GRL_CFG4, CFG4_MHL_MODE);

	if (mode->flags & DRM_MODE_FLAG_INTERLACE &&
	    mode->clock == 74250 &&
	    mode->vdisplay == 1080)
		mtk_hdmi_clear_bits(hdmi, GRL_CFG2, CFG2_MHL_DE_SEL);
	else
		mtk_hdmi_set_bits(hdmi, GRL_CFG2, CFG2_MHL_DE_SEL);
}
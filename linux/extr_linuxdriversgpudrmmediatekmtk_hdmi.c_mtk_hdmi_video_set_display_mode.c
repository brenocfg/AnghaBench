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
struct mtk_hdmi {int /*<<< orphan*/  dvi_mode; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_hdmi_hw_enable_dvi_mode (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_enable_notice (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_msic_setting (struct mtk_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_ncts_auto_write_enable (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_reset (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_write_int_mask (struct mtk_hdmi*,int) ; 

__attribute__((used)) static void mtk_hdmi_video_set_display_mode(struct mtk_hdmi *hdmi,
					    struct drm_display_mode *mode)
{
	mtk_hdmi_hw_reset(hdmi);
	mtk_hdmi_hw_enable_notice(hdmi, true);
	mtk_hdmi_hw_write_int_mask(hdmi, 0xff);
	mtk_hdmi_hw_enable_dvi_mode(hdmi, hdmi->dvi_mode);
	mtk_hdmi_hw_ncts_auto_write_enable(hdmi, true);

	mtk_hdmi_hw_msic_setting(hdmi, mode);
}
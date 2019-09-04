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
struct mtk_hdmi {int powered; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct mtk_hdmi* hdmi_ctx_from_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_1p4_version_enable (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_make_reg_writable (struct mtk_hdmi*,int) ; 

__attribute__((used)) static void mtk_hdmi_bridge_post_disable(struct drm_bridge *bridge)
{
	struct mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	if (!hdmi->powered)
		return;

	mtk_hdmi_hw_1p4_version_enable(hdmi, true);
	mtk_hdmi_hw_make_reg_writable(hdmi, false);

	hdmi->powered = false;
}
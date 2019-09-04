#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {TYPE_5__* crtc; } ;
struct hdmi_context {TYPE_3__* drv_data; TYPE_6__ encoder; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_11__ {TYPE_4__* state; } ;
struct TYPE_10__ {struct drm_display_mode mode; } ;
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_9__ {TYPE_2__ phy_confs; } ;
struct TYPE_7__ {int /*<<< orphan*/ * conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  hdmi_clk_set_parents (struct hdmi_context*,int) ; 
 int hdmi_find_phy_conf (struct hdmi_context*,int) ; 
 int /*<<< orphan*/  hdmiphy_conf_reset (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmiphy_enable_mode_set (struct hdmi_context*,int) ; 
 int hdmiphy_reg_write_buf (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hdmiphy_wait_for_pll (struct hdmi_context*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hdmiphy_conf_apply(struct hdmi_context *hdata)
{
	struct drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	int ret;
	const u8 *phy_conf;

	ret = hdmi_find_phy_conf(hdata, m->clock * 1000);
	if (ret < 0) {
		DRM_ERROR("failed to find hdmiphy conf\n");
		return;
	}
	phy_conf = hdata->drv_data->phy_confs.data[ret].conf;

	hdmi_clk_set_parents(hdata, false);

	hdmiphy_conf_reset(hdata);

	hdmiphy_enable_mode_set(hdata, true);
	ret = hdmiphy_reg_write_buf(hdata, 0, phy_conf, 32);
	if (ret) {
		DRM_ERROR("failed to configure hdmiphy\n");
		return;
	}
	hdmiphy_enable_mode_set(hdata, false);
	hdmi_clk_set_parents(hdata, true);
	usleep_range(10000, 12000);
	hdmiphy_wait_for_pll(hdata);
}
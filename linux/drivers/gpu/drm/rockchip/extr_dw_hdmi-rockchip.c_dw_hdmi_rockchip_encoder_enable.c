#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_hdmi {TYPE_2__* dev; int /*<<< orphan*/  grf_clk; TYPE_1__* chip_data; int /*<<< orphan*/  regmap; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {scalar_t__ lcdsel_grf_reg; int /*<<< orphan*/  lcdsel_big; int /*<<< orphan*/  lcdsel_lit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int drm_of_encoder_active_endpoint_id (int /*<<< orphan*/ ,struct drm_encoder*) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rockchip_hdmi* to_rockchip_hdmi (struct drm_encoder*) ; 

__attribute__((used)) static void dw_hdmi_rockchip_encoder_enable(struct drm_encoder *encoder)
{
	struct rockchip_hdmi *hdmi = to_rockchip_hdmi(encoder);
	u32 val;
	int ret;

	if (hdmi->chip_data->lcdsel_grf_reg < 0)
		return;

	ret = drm_of_encoder_active_endpoint_id(hdmi->dev->of_node, encoder);
	if (ret)
		val = hdmi->chip_data->lcdsel_lit;
	else
		val = hdmi->chip_data->lcdsel_big;

	ret = clk_prepare_enable(hdmi->grf_clk);
	if (ret < 0) {
		DRM_DEV_ERROR(hdmi->dev, "failed to enable grfclk %d\n", ret);
		return;
	}

	ret = regmap_write(hdmi->regmap, hdmi->chip_data->lcdsel_grf_reg, val);
	if (ret != 0)
		DRM_DEV_ERROR(hdmi->dev, "Could not write to GRF: %d\n", ret);

	clk_disable_unprepare(hdmi->grf_clk);
	DRM_DEV_DEBUG(hdmi->dev, "vop %s output to hdmi\n",
		      ret ? "LIT" : "BIG");
}
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
struct rockchip_hdmi {int /*<<< orphan*/  regmap; } ;
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD_UPDATE (int,int) ; 
 int /*<<< orphan*/  RK3228_GRF_SOC_CON2 ; 
 int /*<<< orphan*/  RK3228_GRF_SOC_CON6 ; 
 int RK3228_HDMI_HPD_VSEL ; 
 int RK3228_HDMI_SCLIN_MSK ; 
 int RK3228_HDMI_SCL_VSEL ; 
 int RK3228_HDMI_SDAIN_MSK ; 
 int RK3228_HDMI_SDA_VSEL ; 
 int /*<<< orphan*/  dw_hdmi_phy_setup_hpd (struct dw_hdmi*,void*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_rk3228_setup_hpd(struct dw_hdmi *dw_hdmi, void *data)
{
	struct rockchip_hdmi *hdmi = (struct rockchip_hdmi *)data;

	dw_hdmi_phy_setup_hpd(dw_hdmi, data);

	regmap_write(hdmi->regmap,
		RK3228_GRF_SOC_CON6,
		HIWORD_UPDATE(RK3228_HDMI_HPD_VSEL | RK3228_HDMI_SDA_VSEL |
			      RK3228_HDMI_SCL_VSEL,
			      RK3228_HDMI_HPD_VSEL | RK3228_HDMI_SDA_VSEL |
			      RK3228_HDMI_SCL_VSEL));

	regmap_write(hdmi->regmap,
		RK3228_GRF_SOC_CON2,
		HIWORD_UPDATE(RK3228_HDMI_SDAIN_MSK | RK3228_HDMI_SCLIN_MSK,
			      RK3228_HDMI_SDAIN_MSK | RK3228_HDMI_SCLIN_MSK));
}
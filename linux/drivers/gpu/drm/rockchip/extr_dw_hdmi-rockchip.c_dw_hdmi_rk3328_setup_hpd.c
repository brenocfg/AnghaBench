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
 int /*<<< orphan*/  RK3328_GRF_SOC_CON2 ; 
 int /*<<< orphan*/  RK3328_GRF_SOC_CON3 ; 
 int /*<<< orphan*/  RK3328_GRF_SOC_CON4 ; 
 int RK3328_HDMI_CEC5V_GRF ; 
 int RK3328_HDMI_CEC_5V ; 
 int RK3328_HDMI_HPD5V_GRF ; 
 int RK3328_HDMI_HPD_5V ; 
 int RK3328_HDMI_HPD_IOE ; 
 int RK3328_HDMI_HPD_SARADC ; 
 int RK3328_HDMI_SCL5V_GRF ; 
 int RK3328_HDMI_SCLIN_MSK ; 
 int RK3328_HDMI_SCL_5V ; 
 int RK3328_HDMI_SDA5V_GRF ; 
 int RK3328_HDMI_SDAIN_MSK ; 
 int RK3328_HDMI_SDA_5V ; 
 int /*<<< orphan*/  dw_hdmi_phy_setup_hpd (struct dw_hdmi*,void*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_rk3328_setup_hpd(struct dw_hdmi *dw_hdmi, void *data)
{
	struct rockchip_hdmi *hdmi = (struct rockchip_hdmi *)data;

	dw_hdmi_phy_setup_hpd(dw_hdmi, data);

	/* Enable and map pins to 3V grf-controlled io-voltage */
	regmap_write(hdmi->regmap,
		RK3328_GRF_SOC_CON4,
		HIWORD_UPDATE(0, RK3328_HDMI_HPD_SARADC | RK3328_HDMI_CEC_5V |
				 RK3328_HDMI_SDA_5V | RK3328_HDMI_SCL_5V |
				 RK3328_HDMI_HPD_5V));
	regmap_write(hdmi->regmap,
		RK3328_GRF_SOC_CON3,
		HIWORD_UPDATE(0, RK3328_HDMI_SDA5V_GRF | RK3328_HDMI_SCL5V_GRF |
				 RK3328_HDMI_HPD5V_GRF |
				 RK3328_HDMI_CEC5V_GRF));
	regmap_write(hdmi->regmap,
		RK3328_GRF_SOC_CON2,
		HIWORD_UPDATE(RK3328_HDMI_SDAIN_MSK | RK3328_HDMI_SCLIN_MSK,
			      RK3328_HDMI_SDAIN_MSK | RK3328_HDMI_SCLIN_MSK |
			      RK3328_HDMI_HPD_IOE));
}
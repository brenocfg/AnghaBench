#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_hdmi_phy {TYPE_1__* conf; } ;
struct mtk_hdmi {scalar_t__ sys_offset; int /*<<< orphan*/  sys_regmap; int /*<<< orphan*/  phy; } ;
struct arm_smccc_res {int dummy; } ;
struct TYPE_2__ {scalar_t__ tz_disabled; } ;

/* Variables and functions */
 int ANLG_ON ; 
 int HDMI_ON ; 
 int HDMI_PCLK_FREE_RUN ; 
 scalar_t__ HDMI_SYS_CFG1C ; 
 scalar_t__ HDMI_SYS_CFG20 ; 
 int /*<<< orphan*/  MTK_SIP_SET_AUTHORIZED_SECURE_REG ; 
 int /*<<< orphan*/  arm_smccc_smc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 
 struct mtk_hdmi_phy* phy_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void mtk_hdmi_hw_make_reg_writable(struct mtk_hdmi *hdmi, bool enable)
{
	struct arm_smccc_res res;
	struct mtk_hdmi_phy *hdmi_phy = phy_get_drvdata(hdmi->phy);

	/*
	 * MT8173 HDMI hardware has an output control bit to enable/disable HDMI
	 * output. This bit can only be controlled in ARM supervisor mode.
	 * The ARM trusted firmware provides an API for the HDMI driver to set
	 * this control bit to enable HDMI output in supervisor mode.
	 */
	if (hdmi_phy->conf && hdmi_phy->conf->tz_disabled)
		regmap_update_bits(hdmi->sys_regmap,
				   hdmi->sys_offset + HDMI_SYS_CFG20,
				   0x80008005, enable ? 0x80000005 : 0x8000);
	else
		arm_smccc_smc(MTK_SIP_SET_AUTHORIZED_SECURE_REG, 0x14000904,
			      0x80000000, 0, 0, 0, 0, 0, &res);

	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   HDMI_PCLK_FREE_RUN, enable ? HDMI_PCLK_FREE_RUN : 0);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   HDMI_ON | ANLG_ON, enable ? (HDMI_ON | ANLG_ON) : 0);
}
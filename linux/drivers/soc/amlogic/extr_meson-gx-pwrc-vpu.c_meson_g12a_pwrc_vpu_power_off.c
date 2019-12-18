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
struct meson_gx_pwrc_vpu {int /*<<< orphan*/  vapb_clk; int /*<<< orphan*/  vpu_clk; int /*<<< orphan*/  regmap_ao; int /*<<< orphan*/  regmap_hhi; } ;
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_RTI_GEN_PWR_SLEEP0 ; 
 int BIT (int) ; 
 int GEN_PWR_VPU_HDMI ; 
 int GEN_PWR_VPU_HDMI_ISO ; 
 int /*<<< orphan*/  HHI_MEM_PD_REG0 ; 
 int /*<<< orphan*/  HHI_VPU_MEM_PD_REG0 ; 
 int /*<<< orphan*/  HHI_VPU_MEM_PD_REG1 ; 
 int /*<<< orphan*/  HHI_VPU_MEM_PD_REG2 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct meson_gx_pwrc_vpu* genpd_to_pd (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int meson_g12a_pwrc_vpu_power_off(struct generic_pm_domain *genpd)
{
	struct meson_gx_pwrc_vpu *pd = genpd_to_pd(genpd);
	int i;

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI_ISO, GEN_PWR_VPU_HDMI_ISO);
	udelay(20);

	/* Power Down Memories */
	for (i = 0; i < 32; i += 2) {
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG0,
				   0x3 << i, 0x3 << i);
		udelay(5);
	}
	for (i = 0; i < 32; i += 2) {
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG1,
				   0x3 << i, 0x3 << i);
		udelay(5);
	}
	for (i = 0; i < 32; i += 2) {
		regmap_update_bits(pd->regmap_hhi, HHI_VPU_MEM_PD_REG2,
				   0x3 << i, 0x3 << i);
		udelay(5);
	}
	for (i = 8; i < 16; i++) {
		regmap_update_bits(pd->regmap_hhi, HHI_MEM_PD_REG0,
				   BIT(i), BIT(i));
		udelay(5);
	}
	udelay(20);

	regmap_update_bits(pd->regmap_ao, AO_RTI_GEN_PWR_SLEEP0,
			   GEN_PWR_VPU_HDMI, GEN_PWR_VPU_HDMI);

	msleep(20);

	clk_disable_unprepare(pd->vpu_clk);
	clk_disable_unprepare(pd->vapb_clk);

	return 0;
}
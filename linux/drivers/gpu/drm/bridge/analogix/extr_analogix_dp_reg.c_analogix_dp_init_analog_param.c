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
typedef  int u32 ;
struct analogix_dp_device {scalar_t__ reg_base; TYPE_1__* plat_data; } ;
struct TYPE_2__ {scalar_t__ dev_type; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_ANALOG_CTL_1 ; 
 scalar_t__ ANALOGIX_DP_ANALOG_CTL_2 ; 
 scalar_t__ ANALOGIX_DP_ANALOG_CTL_3 ; 
 scalar_t__ ANALOGIX_DP_PLL_FILTER_CTL_1 ; 
 scalar_t__ ANALOGIX_DP_PLL_REG_1 ; 
 scalar_t__ ANALOGIX_DP_PLL_REG_2 ; 
 scalar_t__ ANALOGIX_DP_PLL_REG_3 ; 
 scalar_t__ ANALOGIX_DP_PLL_REG_4 ; 
 scalar_t__ ANALOGIX_DP_PLL_REG_5 ; 
 scalar_t__ ANALOGIX_DP_TX_AMP_TUNING_CTL ; 
 int AUX_TERMINAL_CTRL_50_OHM ; 
 int CH0_AMP_400_MV ; 
 int CH1_AMP_400_MV ; 
 int CH2_AMP_400_MV ; 
 int CH3_AMP_400_MV ; 
 int DRIVE_DVDD_BIT_1_0625V ; 
 int PD_RING_OSC ; 
 int REF_CLK_24M ; 
 int REF_CLK_MASK ; 
 scalar_t__ RK3288_DP ; 
 int SEL_24M ; 
 int TX_CUR1_2X ; 
 int TX_CUR_16_MA ; 
 int TX_DVDD_BIT_1_0625V ; 
 int TX_TERMINAL_CTRL_50_OHM ; 
 int VCO_BIT_600_MICRO ; 
 scalar_t__ is_rockchip (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_init_analog_param(struct analogix_dp_device *dp)
{
	u32 reg;

	reg = TX_TERMINAL_CTRL_50_OHM;
	writel(reg, dp->reg_base + ANALOGIX_DP_ANALOG_CTL_1);

	reg = SEL_24M | TX_DVDD_BIT_1_0625V;
	writel(reg, dp->reg_base + ANALOGIX_DP_ANALOG_CTL_2);

	if (dp->plat_data && is_rockchip(dp->plat_data->dev_type)) {
		reg = REF_CLK_24M;
		if (dp->plat_data->dev_type == RK3288_DP)
			reg ^= REF_CLK_MASK;

		writel(reg, dp->reg_base + ANALOGIX_DP_PLL_REG_1);
		writel(0x95, dp->reg_base + ANALOGIX_DP_PLL_REG_2);
		writel(0x40, dp->reg_base + ANALOGIX_DP_PLL_REG_3);
		writel(0x58, dp->reg_base + ANALOGIX_DP_PLL_REG_4);
		writel(0x22, dp->reg_base + ANALOGIX_DP_PLL_REG_5);
	}

	reg = DRIVE_DVDD_BIT_1_0625V | VCO_BIT_600_MICRO;
	writel(reg, dp->reg_base + ANALOGIX_DP_ANALOG_CTL_3);

	reg = PD_RING_OSC | AUX_TERMINAL_CTRL_50_OHM |
		TX_CUR1_2X | TX_CUR_16_MA;
	writel(reg, dp->reg_base + ANALOGIX_DP_PLL_FILTER_CTL_1);

	reg = CH3_AMP_400_MV | CH2_AMP_400_MV |
		CH1_AMP_400_MV | CH0_AMP_400_MV;
	writel(reg, dp->reg_base + ANALOGIX_DP_TX_AMP_TUNING_CTL);
}
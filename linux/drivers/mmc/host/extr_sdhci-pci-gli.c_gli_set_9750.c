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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLI_9750_DRIVING_1_VALUE ; 
 int /*<<< orphan*/  GLI_9750_DRIVING_2_VALUE ; 
 int /*<<< orphan*/  GLI_9750_MISC_RX_INV_VALUE ; 
 int /*<<< orphan*/  GLI_9750_MISC_TX1_DLY_VALUE ; 
 int /*<<< orphan*/  GLI_9750_MISC_TX1_INV_VALUE ; 
 int /*<<< orphan*/  GLI_9750_PLL_TX2_DLY_VALUE ; 
 int /*<<< orphan*/  GLI_9750_PLL_TX2_INV_VALUE ; 
 int /*<<< orphan*/  GLI_9750_SW_CTRL_4_VALUE ; 
 int /*<<< orphan*/  GLI_9750_TUNING_CONTROL_EN_OFF ; 
 int /*<<< orphan*/  GLI_9750_TUNING_CONTROL_EN_ON ; 
 int /*<<< orphan*/  GLI_9750_TUNING_CONTROL_GLITCH_1_VALUE ; 
 int /*<<< orphan*/  GLI_9750_TUNING_CONTROL_GLITCH_2_VALUE ; 
 int /*<<< orphan*/  GLI_9750_TUNING_PARAMETERS_RX_DLY_VALUE ; 
 int /*<<< orphan*/  SDHCI_CTRL_TUNED_CLK ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_DRIVING ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_DRIVING_1 ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_DRIVING_2 ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_MISC ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_MISC_RX_INV ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_MISC_TX1_DLY ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_MISC_TX1_INV ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_PLL ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_PLL_TX2_DLY ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_PLL_TX2_INV ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_SW_CTRL ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_SW_CTRL_4 ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_TUNING_CONTROL ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_TUNING_CONTROL_EN ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_1 ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_2 ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_TUNING_PARAMETERS ; 
 int /*<<< orphan*/  SDHCI_GLI_9750_TUNING_PARAMETERS_RX_DLY ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  gl9750_wt_off (struct sdhci_host*) ; 
 int /*<<< orphan*/  gl9750_wt_on (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gli_set_9750(struct sdhci_host *host)
{
	u32 driving_value;
	u32 pll_value;
	u32 sw_ctrl_value;
	u32 misc_value;
	u32 parameter_value;
	u32 control_value;
	u16 ctrl2;

	gl9750_wt_on(host);

	driving_value = sdhci_readl(host, SDHCI_GLI_9750_DRIVING);
	pll_value = sdhci_readl(host, SDHCI_GLI_9750_PLL);
	sw_ctrl_value = sdhci_readl(host, SDHCI_GLI_9750_SW_CTRL);
	misc_value = sdhci_readl(host, SDHCI_GLI_9750_MISC);
	parameter_value = sdhci_readl(host, SDHCI_GLI_9750_TUNING_PARAMETERS);
	control_value = sdhci_readl(host, SDHCI_GLI_9750_TUNING_CONTROL);

	driving_value &= ~(SDHCI_GLI_9750_DRIVING_1);
	driving_value &= ~(SDHCI_GLI_9750_DRIVING_2);
	driving_value |= FIELD_PREP(SDHCI_GLI_9750_DRIVING_1,
				    GLI_9750_DRIVING_1_VALUE);
	driving_value |= FIELD_PREP(SDHCI_GLI_9750_DRIVING_2,
				    GLI_9750_DRIVING_2_VALUE);
	sdhci_writel(host, driving_value, SDHCI_GLI_9750_DRIVING);

	sw_ctrl_value &= ~SDHCI_GLI_9750_SW_CTRL_4;
	sw_ctrl_value |= FIELD_PREP(SDHCI_GLI_9750_SW_CTRL_4,
				    GLI_9750_SW_CTRL_4_VALUE);
	sdhci_writel(host, sw_ctrl_value, SDHCI_GLI_9750_SW_CTRL);

	/* reset the tuning flow after reinit and before starting tuning */
	pll_value &= ~SDHCI_GLI_9750_PLL_TX2_INV;
	pll_value &= ~SDHCI_GLI_9750_PLL_TX2_DLY;
	pll_value |= FIELD_PREP(SDHCI_GLI_9750_PLL_TX2_INV,
				GLI_9750_PLL_TX2_INV_VALUE);
	pll_value |= FIELD_PREP(SDHCI_GLI_9750_PLL_TX2_DLY,
				GLI_9750_PLL_TX2_DLY_VALUE);

	misc_value &= ~SDHCI_GLI_9750_MISC_TX1_INV;
	misc_value &= ~SDHCI_GLI_9750_MISC_RX_INV;
	misc_value &= ~SDHCI_GLI_9750_MISC_TX1_DLY;
	misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_TX1_INV,
				 GLI_9750_MISC_TX1_INV_VALUE);
	misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_RX_INV,
				 GLI_9750_MISC_RX_INV_VALUE);
	misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_TX1_DLY,
				 GLI_9750_MISC_TX1_DLY_VALUE);

	parameter_value &= ~SDHCI_GLI_9750_TUNING_PARAMETERS_RX_DLY;
	parameter_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_PARAMETERS_RX_DLY,
				      GLI_9750_TUNING_PARAMETERS_RX_DLY_VALUE);

	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_1;
	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_2;
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_1,
				    GLI_9750_TUNING_CONTROL_GLITCH_1_VALUE);
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_2,
				    GLI_9750_TUNING_CONTROL_GLITCH_2_VALUE);

	sdhci_writel(host, pll_value, SDHCI_GLI_9750_PLL);
	sdhci_writel(host, misc_value, SDHCI_GLI_9750_MISC);

	/* disable tuned clk */
	ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctrl2 &= ~SDHCI_CTRL_TUNED_CLK;
	sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);

	/* enable tuning parameters control */
	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_EN;
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_EN,
				    GLI_9750_TUNING_CONTROL_EN_ON);
	sdhci_writel(host, control_value, SDHCI_GLI_9750_TUNING_CONTROL);

	/* write tuning parameters */
	sdhci_writel(host, parameter_value, SDHCI_GLI_9750_TUNING_PARAMETERS);

	/* disable tuning parameters control */
	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_EN;
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_EN,
				    GLI_9750_TUNING_CONTROL_EN_OFF);
	sdhci_writel(host, control_value, SDHCI_GLI_9750_TUNING_CONTROL);

	/* clear tuned clk */
	ctrl2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctrl2 &= ~SDHCI_CTRL_TUNED_CLK;
	sdhci_writew(host, ctrl2, SDHCI_HOST_CONTROL2);

	gl9750_wt_off(host);
}
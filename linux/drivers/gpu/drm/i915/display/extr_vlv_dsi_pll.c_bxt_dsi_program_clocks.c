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
struct TYPE_2__ {int ctrl; } ;
struct intel_crtc_state {TYPE_1__ dsi_pll; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int BXT_DSI_PLL_RATIO_MASK ; 
 int BXT_MIPI_8X_BY3_DIVIDER (int,int) ; 
 int BXT_MIPI_8X_BY3_DIVIDER_MASK (int) ; 
 int /*<<< orphan*/  BXT_MIPI_CLOCK_CTL ; 
 int BXT_MIPI_RX_ESCLK_LOWER_DIVIDER (int,int) ; 
 int BXT_MIPI_RX_ESCLK_LOWER_FIXDIV_MASK (int) ; 
 int BXT_MIPI_RX_ESCLK_UPPER_DIVIDER (int,int) ; 
 int BXT_MIPI_RX_ESCLK_UPPER_FIXDIV_MASK (int) ; 
 int BXT_MIPI_TX_ESCLK_DIVIDER (int,int) ; 
 int BXT_MIPI_TX_ESCLK_FIXDIV_MASK (int) ; 
 int BXT_REF_CLOCK_KHZ ; 
 int DIV_ROUND_UP (int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int RX_DIVIDER_BIT_1_2 ; 
 int RX_DIVIDER_BIT_3_4 ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void bxt_dsi_program_clocks(struct drm_device *dev, enum port port,
				   const struct intel_crtc_state *config)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 tmp;
	u32 dsi_rate = 0;
	u32 pll_ratio = 0;
	u32 rx_div;
	u32 tx_div;
	u32 rx_div_upper;
	u32 rx_div_lower;
	u32 mipi_8by3_divider;

	/* Clear old configurations */
	tmp = I915_READ(BXT_MIPI_CLOCK_CTL);
	tmp &= ~(BXT_MIPI_TX_ESCLK_FIXDIV_MASK(port));
	tmp &= ~(BXT_MIPI_RX_ESCLK_UPPER_FIXDIV_MASK(port));
	tmp &= ~(BXT_MIPI_8X_BY3_DIVIDER_MASK(port));
	tmp &= ~(BXT_MIPI_RX_ESCLK_LOWER_FIXDIV_MASK(port));

	/* Get the current DSI rate(actual) */
	pll_ratio = config->dsi_pll.ctrl & BXT_DSI_PLL_RATIO_MASK;
	dsi_rate = (BXT_REF_CLOCK_KHZ * pll_ratio) / 2;

	/*
	 * tx clock should be <= 20MHz and the div value must be
	 * subtracted by 1 as per bspec
	 */
	tx_div = DIV_ROUND_UP(dsi_rate, 20000) - 1;
	/*
	 * rx clock should be <= 150MHz and the div value must be
	 * subtracted by 1 as per bspec
	 */
	rx_div = DIV_ROUND_UP(dsi_rate, 150000) - 1;

	/*
	 * rx divider value needs to be updated in the
	 * two differnt bit fields in the register hence splitting the
	 * rx divider value accordingly
	 */
	rx_div_lower = rx_div & RX_DIVIDER_BIT_1_2;
	rx_div_upper = (rx_div & RX_DIVIDER_BIT_3_4) >> 2;

	mipi_8by3_divider = 0x2;

	tmp |= BXT_MIPI_8X_BY3_DIVIDER(port, mipi_8by3_divider);
	tmp |= BXT_MIPI_TX_ESCLK_DIVIDER(port, tx_div);
	tmp |= BXT_MIPI_RX_ESCLK_LOWER_DIVIDER(port, rx_div_lower);
	tmp |= BXT_MIPI_RX_ESCLK_UPPER_DIVIDER(port, rx_div_upper);

	I915_WRITE(BXT_MIPI_CLOCK_CTL, tmp);
}
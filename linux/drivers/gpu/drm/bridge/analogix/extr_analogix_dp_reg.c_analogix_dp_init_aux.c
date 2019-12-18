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
struct TYPE_2__ {int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_AUX_CH_DEFER_CTL ; 
 scalar_t__ ANALOGIX_DP_AUX_HW_RETRY_CTL ; 
 scalar_t__ ANALOGIX_DP_FUNC_EN_2 ; 
 scalar_t__ ANALOGIX_DP_INT_STA ; 
 int AUX_BIT_PERIOD_EXPECTED_DELAY (int) ; 
 int /*<<< orphan*/  AUX_BLOCK ; 
 int AUX_ERR ; 
 int AUX_FUNC_EN_N ; 
 int AUX_HW_RETRY_COUNT_SEL (int /*<<< orphan*/ ) ; 
 int AUX_HW_RETRY_INTERVAL_600_MICROSECONDS ; 
 int DEFER_COUNT (int) ; 
 int DEFER_CTRL_EN ; 
 int RPLY_RECEIV ; 
 int /*<<< orphan*/  analogix_dp_reset_aux (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_set_analog_power_down (struct analogix_dp_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_rockchip (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_init_aux(struct analogix_dp_device *dp)
{
	u32 reg;

	/* Clear inerrupts related to AUX channel */
	reg = RPLY_RECEIV | AUX_ERR;
	writel(reg, dp->reg_base + ANALOGIX_DP_INT_STA);

	analogix_dp_set_analog_power_down(dp, AUX_BLOCK, true);
	usleep_range(10, 11);
	analogix_dp_set_analog_power_down(dp, AUX_BLOCK, false);

	analogix_dp_reset_aux(dp);

	/* AUX_BIT_PERIOD_EXPECTED_DELAY doesn't apply to Rockchip IP */
	if (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
		reg = 0;
	else
		reg = AUX_BIT_PERIOD_EXPECTED_DELAY(3);

	/* Disable AUX transaction H/W retry */
	reg |= AUX_HW_RETRY_COUNT_SEL(0) |
	       AUX_HW_RETRY_INTERVAL_600_MICROSECONDS;

	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_HW_RETRY_CTL);

	/* Receive AUX Channel DEFER commands equal to DEFFER_COUNT*64 */
	reg = DEFER_CTRL_EN | DEFER_COUNT(1);
	writel(reg, dp->reg_base + ANALOGIX_DP_AUX_CH_DEFER_CTL);

	/* Enable AUX channel module */
	reg = readl(dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	reg &= ~AUX_FUNC_EN_N;
	writel(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
}
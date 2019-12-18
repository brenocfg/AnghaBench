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
typedef  int u32 ;
struct analogix_dp_device {scalar_t__ reg_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_COMMON_INT_STA_1 ; 
 scalar_t__ ANALOGIX_DP_DEBUG_CTL ; 
 scalar_t__ ANALOGIX_DP_FUNC_EN_2 ; 
 int AUX_FUNC_EN_N ; 
 int DP_TIMEOUT_LOOP_COUNT ; 
 int ETIMEDOUT ; 
 int F_PLL_LOCK ; 
 int LS_CLK_DOMAIN_FUNC_EN_N ; 
 int PLL_LOCK_CHG ; 
 int PLL_LOCK_CTRL ; 
 scalar_t__ PLL_UNLOCKED ; 
 int /*<<< orphan*/  POWER_ALL ; 
 int SERDES_FIFO_FUNC_EN_N ; 
 scalar_t__ analogix_dp_get_pll_lock_status (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_set_analog_power_down (struct analogix_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_set_pll_power_down (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int analogix_dp_init_analog_func(struct analogix_dp_device *dp)
{
	u32 reg;
	int timeout_loop = 0;

	analogix_dp_set_analog_power_down(dp, POWER_ALL, 0);

	reg = PLL_LOCK_CHG;
	writel(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_1);

	reg = readl(dp->reg_base + ANALOGIX_DP_DEBUG_CTL);
	reg &= ~(F_PLL_LOCK | PLL_LOCK_CTRL);
	writel(reg, dp->reg_base + ANALOGIX_DP_DEBUG_CTL);

	/* Power up PLL */
	if (analogix_dp_get_pll_lock_status(dp) == PLL_UNLOCKED) {
		analogix_dp_set_pll_power_down(dp, 0);

		while (analogix_dp_get_pll_lock_status(dp) == PLL_UNLOCKED) {
			timeout_loop++;
			if (DP_TIMEOUT_LOOP_COUNT < timeout_loop) {
				dev_err(dp->dev, "failed to get pll lock status\n");
				return -ETIMEDOUT;
			}
			usleep_range(10, 20);
		}
	}

	/* Enable Serdes FIFO function and Link symbol clock domain module */
	reg = readl(dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	reg &= ~(SERDES_FIFO_FUNC_EN_N | LS_CLK_DOMAIN_FUNC_EN_N
		| AUX_FUNC_EN_N);
	writel(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	return 0;
}
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
struct tegra_p2u {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2U_PERIODIC_EQ_CTRL_GEN3 ; 
 int /*<<< orphan*/  P2U_PERIODIC_EQ_CTRL_GEN3_INIT_PRESET_EQ_TRAIN_EN ; 
 int /*<<< orphan*/  P2U_PERIODIC_EQ_CTRL_GEN3_PERIODIC_EQ_EN ; 
 int /*<<< orphan*/  P2U_PERIODIC_EQ_CTRL_GEN4 ; 
 int /*<<< orphan*/  P2U_PERIODIC_EQ_CTRL_GEN4_INIT_PRESET_EQ_TRAIN_EN ; 
 int /*<<< orphan*/  P2U_RX_DEBOUNCE_TIME ; 
 int /*<<< orphan*/  P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_MASK ; 
 int /*<<< orphan*/  P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_VAL ; 
 int /*<<< orphan*/  p2u_readl (struct tegra_p2u*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2u_writel (struct tegra_p2u*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_p2u* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int tegra_p2u_power_on(struct phy *x)
{
	struct tegra_p2u *phy = phy_get_drvdata(x);
	u32 val;

	val = p2u_readl(phy, P2U_PERIODIC_EQ_CTRL_GEN3);
	val &= ~P2U_PERIODIC_EQ_CTRL_GEN3_PERIODIC_EQ_EN;
	val |= P2U_PERIODIC_EQ_CTRL_GEN3_INIT_PRESET_EQ_TRAIN_EN;
	p2u_writel(phy, val, P2U_PERIODIC_EQ_CTRL_GEN3);

	val = p2u_readl(phy, P2U_PERIODIC_EQ_CTRL_GEN4);
	val |= P2U_PERIODIC_EQ_CTRL_GEN4_INIT_PRESET_EQ_TRAIN_EN;
	p2u_writel(phy, val, P2U_PERIODIC_EQ_CTRL_GEN4);

	val = p2u_readl(phy, P2U_RX_DEBOUNCE_TIME);
	val &= ~P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_MASK;
	val |= P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_VAL;
	p2u_writel(phy, val, P2U_RX_DEBOUNCE_TIME);

	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct mwl8k_priv {int sw_scan_start; int /*<<< orphan*/  hw; scalar_t__ regs; scalar_t__ channel_time; int /*<<< orphan*/  ap_fw; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBU_AVG_NOISE_VAL ; 
 scalar_t__ BBU_RXRDY_CNT_REG ; 
 scalar_t__ NOK_CCA_CNT_REG ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  mwl8k_cmd_bbp_reg_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwl8k_sw_scan_start(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				const u8 *mac_addr)
{
	struct mwl8k_priv *priv = hw->priv;
	u8 tmp;

	if (!priv->ap_fw)
		return;

	/* clear all stats */
	priv->channel_time = 0;
	ioread32(priv->regs + BBU_RXRDY_CNT_REG);
	ioread32(priv->regs + NOK_CCA_CNT_REG);
	mwl8k_cmd_bbp_reg_access(priv->hw, 0, BBU_AVG_NOISE_VAL, &tmp);

	priv->sw_scan_start = true;
}
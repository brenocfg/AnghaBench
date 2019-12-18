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
struct rtl8xxxu_priv {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rtl8xxxu_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_DISABLE_TSF_UPDATE ; 
 int /*<<< orphan*/  REG_BEACON_CTRL ; 
 int /*<<< orphan*/  rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8xxxu_sw_scan_complete(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif)
{
	struct rtl8xxxu_priv *priv = hw->priv;
	u8 val8;

	val8 = rtl8xxxu_read8(priv, REG_BEACON_CTRL);
	val8 &= ~BEACON_DISABLE_TSF_UPDATE;
	rtl8xxxu_write8(priv, REG_BEACON_CTRL, val8);
}
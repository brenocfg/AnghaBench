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
struct rtl8180_priv {int dummy; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8225SE_ANAPARAM2_OFF ; 
 int /*<<< orphan*/  RTL8225SE_ANAPARAM_OFF ; 
 int /*<<< orphan*/  rtl8180_set_anaparam (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam2 (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8187se_rf_writereg (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225se_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void rtl8225se_rf_stop(struct ieee80211_hw *dev)
{
	/* checked for 8187se */
	struct rtl8180_priv *priv = dev->priv;

	/* turn off BB RXIQ matrix to cut off rx signal */
	rtl8225se_write_phy_ofdm(dev, 0x10, 0x00);
	rtl8225se_write_phy_ofdm(dev, 0x12, 0x00);
	/* turn off RF */
	rtl8187se_rf_writereg(dev, 0x04, 0x0000);
	rtl8187se_rf_writereg(dev, 0x00, 0x0000);

	usleep_range(1000, 5000);
	/* turn off A/D and D/A */
	rtl8180_set_anaparam(priv, RTL8225SE_ANAPARAM_OFF);
	rtl8180_set_anaparam2(priv, RTL8225SE_ANAPARAM2_OFF);
}
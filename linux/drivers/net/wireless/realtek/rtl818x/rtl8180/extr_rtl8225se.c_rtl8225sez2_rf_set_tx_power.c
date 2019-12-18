#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl8180_priv {TYPE_2__* map; TYPE_1__* channels; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  TX_GAIN_OFDM; int /*<<< orphan*/  TX_GAIN_CCK; } ;
struct TYPE_3__ {int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cck_ofdm_gain_settings ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8225se_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rtl8225sez2_rf_set_tx_power(struct ieee80211_hw *dev, int channel)
{
	struct rtl8180_priv *priv = dev->priv;
	u8 cck_power, ofdm_power;

	cck_power = priv->channels[channel - 1].hw_value & 0xFF;
	if (cck_power > 35)
		cck_power = 35;
	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_CCK,
			 cck_ofdm_gain_settings[cck_power]);

	usleep_range(1000, 5000);
	ofdm_power = priv->channels[channel - 1].hw_value >> 8;
	if (ofdm_power > 35)
		ofdm_power = 35;

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_OFDM,
			 cck_ofdm_gain_settings[ofdm_power]);
	if (ofdm_power < 12) {
		rtl8225se_write_phy_ofdm(dev, 7, 0x5C);
		rtl8225se_write_phy_ofdm(dev, 9, 0x5C);
	}
	if (ofdm_power < 18) {
		rtl8225se_write_phy_ofdm(dev, 7, 0x54);
		rtl8225se_write_phy_ofdm(dev, 9, 0x54);
	} else {
		rtl8225se_write_phy_ofdm(dev, 7, 0x50);
		rtl8225se_write_phy_ofdm(dev, 9, 0x50);
	}

	usleep_range(1000, 5000);
}
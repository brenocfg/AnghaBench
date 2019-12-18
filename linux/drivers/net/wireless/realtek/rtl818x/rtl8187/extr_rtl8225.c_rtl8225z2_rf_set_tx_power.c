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
typedef  int u32 ;
struct rtl8187_priv {int txpwr_base; TYPE_2__* map; TYPE_1__* channels; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  TX_GAIN_OFDM; int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG3; int /*<<< orphan*/  ANAPARAM2; int /*<<< orphan*/  TX_GAIN_CCK; } ;
struct TYPE_3__ {int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8187_RTL8225_ANAPARAM2_ON ; 
 int RTL818X_CONFIG3_ANAPARAM_WRITE ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int min (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl818x_ioread8 (struct rtl8187_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8187_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl8225_write_phy_cck (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8225_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int* rtl8225z2_tx_gain_cck_ofdm ; 
 int* rtl8225z2_tx_power_cck ; 
 int* rtl8225z2_tx_power_cck_ch14 ; 

__attribute__((used)) static void rtl8225z2_rf_set_tx_power(struct ieee80211_hw *dev, int channel)
{
	struct rtl8187_priv *priv = dev->priv;
	u8 cck_power, ofdm_power;
	const u8 *tmp;
	u32 reg;
	int i;

	cck_power = priv->channels[channel - 1].hw_value & 0xF;
	ofdm_power = priv->channels[channel - 1].hw_value >> 4;

	cck_power = min(cck_power, (u8)15);
	cck_power += priv->txpwr_base & 0xF;
	cck_power = min(cck_power, (u8)35);

	if (ofdm_power > (u8)15)
		ofdm_power = 25;
	else
		ofdm_power += 10;
	ofdm_power += priv->txpwr_base >> 4;
	ofdm_power = min(ofdm_power, (u8)35);

	if (channel == 14)
		tmp = rtl8225z2_tx_power_cck_ch14;
	else
		tmp = rtl8225z2_tx_power_cck;

	for (i = 0; i < 8; i++)
		rtl8225_write_phy_cck(dev, 0x44 + i, *tmp++);

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_CCK,
			 rtl8225z2_tx_gain_cck_ofdm[cck_power]);
	msleep(1);

	/* anaparam2 on */
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3,
			reg | RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_iowrite32(priv, &priv->map->ANAPARAM2,
			  RTL8187_RTL8225_ANAPARAM2_ON);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3,
			reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	rtl8225_write_phy_ofdm(dev, 2, 0x42);
	rtl8225_write_phy_ofdm(dev, 5, 0x00);
	rtl8225_write_phy_ofdm(dev, 6, 0x40);
	rtl8225_write_phy_ofdm(dev, 7, 0x00);
	rtl8225_write_phy_ofdm(dev, 8, 0x40);

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_OFDM,
			 rtl8225z2_tx_gain_cck_ofdm[ofdm_power]);
	msleep(1);
}
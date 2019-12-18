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
typedef  int u16 ;
struct rtl818x_rf_ops {int dummy; } ;
struct rtl8180_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  RFPinsEnable; int /*<<< orphan*/  RFPinsSelect; int /*<<< orphan*/  RFPinsOutput; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 struct rtl818x_rf_ops const rtl8225_ops ; 
 int rtl8225_read (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8225_write (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 struct rtl818x_rf_ops const rtl8225z2_ops ; 

const struct rtl818x_rf_ops * rtl8180_detect_rf(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u16 reg8, reg9;

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, 0x0480);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0x0488);
	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, 0x1FFF);
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	msleep(100);

	rtl8225_write(dev, 0, 0x1B7);

	reg8 = rtl8225_read(dev, 8);
	reg9 = rtl8225_read(dev, 9);

	rtl8225_write(dev, 0, 0x0B7);

	if (reg8 != 0x588 || reg9 != 0x700)
		return &rtl8225_ops;

	return &rtl8225z2_ops;
}
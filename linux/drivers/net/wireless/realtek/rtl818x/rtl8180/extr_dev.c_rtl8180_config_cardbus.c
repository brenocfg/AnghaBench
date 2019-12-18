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
typedef  int u8 ;
typedef  int u16 ;
struct rtl8180_priv {scalar_t__ chip_family; TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  FEMR; int /*<<< orphan*/  CONFIG3; } ;

/* Variables and functions */
 int /*<<< orphan*/ * FEMR_SE ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8187SE ; 
 int rtl818x_ioread16 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rtl8180_config_cardbus(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u16 reg16;
	u8 reg8;

	reg8 = rtl818x_ioread8(priv, &priv->map->CONFIG3);
	reg8 |= 1 << 1;
	rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg8);

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) {
		rtl818x_iowrite16(priv, FEMR_SE, 0xffff);
	} else {
		reg16 = rtl818x_ioread16(priv, &priv->map->FEMR);
		reg16 |= (1 << 15) | (1 << 14) | (1 << 4);
		rtl818x_iowrite16(priv, &priv->map->FEMR, reg16);
	}

}
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
struct rtl8187_priv {TYPE_1__* map; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8187_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CMD; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RTL818X_CMD_RESET ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_LOAD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl818x_ioread8 (struct rtl8187_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtl8187_cmd_reset(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	u8 reg;
	int i;

	reg = rtl818x_ioread8(priv, &priv->map->CMD);
	reg &= (1 << 1);
	reg |= RTL818X_CMD_RESET;
	rtl818x_iowrite8(priv, &priv->map->CMD, reg);

	i = 10;
	do {
		msleep(2);
		if (!(rtl818x_ioread8(priv, &priv->map->CMD) &
		      RTL818X_CMD_RESET))
			break;
	} while (--i);

	if (!i) {
		wiphy_err(dev->wiphy, "Reset timeout!\n");
		return -ETIMEDOUT;
	}

	/* reload registers from eeprom */
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_LOAD);

	i = 10;
	do {
		msleep(4);
		if (!(rtl818x_ioread8(priv, &priv->map->EEPROM_CMD) &
		      RTL818X_EEPROM_CMD_CONFIG))
			break;
	} while (--i);

	if (!i) {
		wiphy_err(dev->wiphy, "eeprom reset timeout!\n");
		return -ETIMEDOUT;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl8180_priv {TYPE_3__* pdev; TYPE_2__* map; TYPE_1__* rf; } ;
struct ieee80211_hw {int queues; struct rtl8180_priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG4; int /*<<< orphan*/  CMD; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int RTL818X_CMD_RX_ENABLE ; 
 int RTL818X_CMD_TX_ENABLE ; 
 int RTL818X_CONFIG4_VCOOFF ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8180_free_rx_ring (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8180_free_tx_ring (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8180_int_disable (struct ieee80211_hw*) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8180_stop(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u8 reg;
	int i;

	rtl8180_int_disable(dev);

	reg = rtl818x_ioread8(priv, &priv->map->CMD);
	reg &= ~RTL818X_CMD_TX_ENABLE;
	reg &= ~RTL818X_CMD_RX_ENABLE;
	rtl818x_iowrite8(priv, &priv->map->CMD, reg);

	priv->rf->stop(dev);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG4);
	rtl818x_iowrite8(priv, &priv->map->CONFIG4, reg | RTL818X_CONFIG4_VCOOFF);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	free_irq(priv->pdev->irq, dev);

	rtl8180_free_rx_ring(dev);
	for (i = 0; i < (dev->queues + 1); i++)
		rtl8180_free_tx_ring(dev, i);
}
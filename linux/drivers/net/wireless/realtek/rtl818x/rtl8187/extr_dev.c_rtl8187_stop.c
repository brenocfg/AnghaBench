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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct rtl8187_priv {int /*<<< orphan*/  work; int /*<<< orphan*/  is_rtl8187b; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  anchored; TYPE_3__ b_tx_status; TYPE_2__* map; TYPE_1__* rf; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG4; int /*<<< orphan*/  CMD; int /*<<< orphan*/  INT_MASK; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int RTL818X_CMD_RX_ENABLE ; 
 int RTL818X_CMD_TX_ENABLE ; 
 int RTL818X_CONFIG4_VCOOFF ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8187_set_anaparam (struct rtl8187_priv*,int) ; 
 int rtl818x_ioread8 (struct rtl8187_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8187_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8187_stop(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	struct sk_buff *skb;
	u32 reg;

	mutex_lock(&priv->conf_mutex);
	rtl818x_iowrite16(priv, &priv->map->INT_MASK, 0);

	reg = rtl818x_ioread8(priv, &priv->map->CMD);
	reg &= ~RTL818X_CMD_TX_ENABLE;
	reg &= ~RTL818X_CMD_RX_ENABLE;
	rtl818x_iowrite8(priv, &priv->map->CMD, reg);

	priv->rf->stop(dev);
	rtl8187_set_anaparam(priv, false);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG4);
	rtl818x_iowrite8(priv, &priv->map->CONFIG4, reg | RTL818X_CONFIG4_VCOOFF);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	while ((skb = skb_dequeue(&priv->b_tx_status.queue)))
		dev_kfree_skb_any(skb);

	usb_kill_anchored_urbs(&priv->anchored);
	mutex_unlock(&priv->conf_mutex);

	if (!priv->is_rtl8187b)
		cancel_delayed_work_sync(&priv->work);
}
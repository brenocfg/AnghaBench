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
struct rtl8180_priv {int /*<<< orphan*/  lock; TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  INT_STATUS; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTL818X_INT_RX_ERR ; 
 int RTL818X_INT_RX_OK ; 
 int RTL818X_INT_TXB_ERR ; 
 int RTL818X_INT_TXB_OK ; 
 int RTL818X_INT_TXL_ERR ; 
 int RTL818X_INT_TXL_OK ; 
 int /*<<< orphan*/  rtl8180_handle_rx (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8180_handle_tx (struct ieee80211_hw*,int) ; 
 int rtl818x_ioread16 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t rtl8180_interrupt(int irq, void *dev_id)
{
	struct ieee80211_hw *dev = dev_id;
	struct rtl8180_priv *priv = dev->priv;
	u16 reg;

	spin_lock(&priv->lock);
	reg = rtl818x_ioread16(priv, &priv->map->INT_STATUS);
	if (unlikely(reg == 0xFFFF)) {
		spin_unlock(&priv->lock);
		return IRQ_HANDLED;
	}

	rtl818x_iowrite16(priv, &priv->map->INT_STATUS, reg);

	if (reg & (RTL818X_INT_TXB_OK | RTL818X_INT_TXB_ERR))
		rtl8180_handle_tx(dev, 1);

	if (reg & (RTL818X_INT_TXL_OK | RTL818X_INT_TXL_ERR))
		rtl8180_handle_tx(dev, 0);

	if (reg & (RTL818X_INT_RX_OK | RTL818X_INT_RX_ERR))
		rtl8180_handle_rx(dev);

	spin_unlock(&priv->lock);

	return IRQ_HANDLED;
}
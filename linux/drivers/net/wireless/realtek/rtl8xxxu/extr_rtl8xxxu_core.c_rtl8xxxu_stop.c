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
struct rtl8xxxu_priv {int shutdown; scalar_t__ usb_interrupts; TYPE_1__* fops; int /*<<< orphan*/  int_anchor; int /*<<< orphan*/  tx_anchor; int /*<<< orphan*/  rx_anchor; int /*<<< orphan*/  rx_urb_lock; } ;
struct ieee80211_hw {struct rtl8xxxu_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_rf ) (struct rtl8xxxu_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RXFLTMAP0 ; 
 int /*<<< orphan*/  REG_RXFLTMAP2 ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 int /*<<< orphan*/  REG_USB_HIMR ; 
 int /*<<< orphan*/  rtl8xxxu_free_rx_resources (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_free_tx_resources (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8xxxu_stop(struct ieee80211_hw *hw)
{
	struct rtl8xxxu_priv *priv = hw->priv;
	unsigned long flags;

	rtl8xxxu_write8(priv, REG_TXPAUSE, 0xff);

	rtl8xxxu_write16(priv, REG_RXFLTMAP0, 0x0000);
	rtl8xxxu_write16(priv, REG_RXFLTMAP2, 0x0000);

	spin_lock_irqsave(&priv->rx_urb_lock, flags);
	priv->shutdown = true;
	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);

	usb_kill_anchored_urbs(&priv->rx_anchor);
	usb_kill_anchored_urbs(&priv->tx_anchor);
	if (priv->usb_interrupts)
		usb_kill_anchored_urbs(&priv->int_anchor);

	rtl8xxxu_write8(priv, REG_TXPAUSE, 0xff);

	priv->fops->disable_rf(priv);

	/*
	 * Disable interrupts
	 */
	if (priv->usb_interrupts)
		rtl8xxxu_write32(priv, REG_USB_HIMR, 0);

	rtl8xxxu_free_rx_resources(priv);
	rtl8xxxu_free_tx_resources(priv);
}
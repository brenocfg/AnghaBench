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
struct wireless_dev {scalar_t__ iftype; } ;
struct wil6210_priv {int tx_max_burst_duration; int tx_interframe_timeout; int rx_max_burst_duration; int rx_interframe_timeout; TYPE_1__* main_ndev; } ;
struct TYPE_2__ {struct wireless_dev* ieee80211_ptr; } ;

/* Variables and functions */
 int BIT_DMA_ITR_RX_CNT_CTL_CLR ; 
 int BIT_DMA_ITR_RX_CNT_CTL_EN ; 
 int BIT_DMA_ITR_RX_CNT_CTL_EXT_TIC_SEL ; 
 int BIT_DMA_ITR_RX_IDL_CNT_CTL_CLR ; 
 int BIT_DMA_ITR_RX_IDL_CNT_CTL_EN ; 
 int BIT_DMA_ITR_RX_IDL_CNT_CTL_EXT_TIC_SEL ; 
 int BIT_DMA_ITR_TX_CNT_CTL_CLR ; 
 int BIT_DMA_ITR_TX_CNT_CTL_EN ; 
 int BIT_DMA_ITR_TX_CNT_CTL_EXT_TIC_SEL ; 
 int BIT_DMA_ITR_TX_IDL_CNT_CTL_CLR ; 
 int BIT_DMA_ITR_TX_IDL_CNT_CTL_EN ; 
 int BIT_DMA_ITR_TX_IDL_CNT_CTL_EXT_TIC_SEL ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  RGF_DMA_ITR_RX_CNT_CTL ; 
 int /*<<< orphan*/  RGF_DMA_ITR_RX_CNT_TRSH ; 
 int /*<<< orphan*/  RGF_DMA_ITR_RX_IDL_CNT_CTL ; 
 int /*<<< orphan*/  RGF_DMA_ITR_RX_IDL_CNT_TRSH ; 
 int /*<<< orphan*/  RGF_DMA_ITR_TX_CNT_CTL ; 
 int /*<<< orphan*/  RGF_DMA_ITR_TX_CNT_TRSH ; 
 int /*<<< orphan*/  RGF_DMA_ITR_TX_IDL_CNT_CTL ; 
 int /*<<< orphan*/  RGF_DMA_ITR_TX_IDL_CNT_TRSH ; 
 int /*<<< orphan*/  wil_dbg_irq (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_w (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 

void wil_configure_interrupt_moderation(struct wil6210_priv *wil)
{
	struct wireless_dev *wdev = wil->main_ndev->ieee80211_ptr;

	wil_dbg_irq(wil, "configure_interrupt_moderation\n");

	/* disable interrupt moderation for monitor
	 * to get better timestamp precision
	 */
	if (wdev->iftype == NL80211_IFTYPE_MONITOR)
		return;

	/* Disable and clear tx counter before (re)configuration */
	wil_w(wil, RGF_DMA_ITR_TX_CNT_CTL, BIT_DMA_ITR_TX_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_TX_CNT_TRSH, wil->tx_max_burst_duration);
	wil_info(wil, "set ITR_TX_CNT_TRSH = %d usec\n",
		 wil->tx_max_burst_duration);
	/* Configure TX max burst duration timer to use usec units */
	wil_w(wil, RGF_DMA_ITR_TX_CNT_CTL,
	      BIT_DMA_ITR_TX_CNT_CTL_EN | BIT_DMA_ITR_TX_CNT_CTL_EXT_TIC_SEL);

	/* Disable and clear tx idle counter before (re)configuration */
	wil_w(wil, RGF_DMA_ITR_TX_IDL_CNT_CTL, BIT_DMA_ITR_TX_IDL_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_TX_IDL_CNT_TRSH, wil->tx_interframe_timeout);
	wil_info(wil, "set ITR_TX_IDL_CNT_TRSH = %d usec\n",
		 wil->tx_interframe_timeout);
	/* Configure TX max burst duration timer to use usec units */
	wil_w(wil, RGF_DMA_ITR_TX_IDL_CNT_CTL, BIT_DMA_ITR_TX_IDL_CNT_CTL_EN |
	      BIT_DMA_ITR_TX_IDL_CNT_CTL_EXT_TIC_SEL);

	/* Disable and clear rx counter before (re)configuration */
	wil_w(wil, RGF_DMA_ITR_RX_CNT_CTL, BIT_DMA_ITR_RX_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_RX_CNT_TRSH, wil->rx_max_burst_duration);
	wil_info(wil, "set ITR_RX_CNT_TRSH = %d usec\n",
		 wil->rx_max_burst_duration);
	/* Configure TX max burst duration timer to use usec units */
	wil_w(wil, RGF_DMA_ITR_RX_CNT_CTL,
	      BIT_DMA_ITR_RX_CNT_CTL_EN | BIT_DMA_ITR_RX_CNT_CTL_EXT_TIC_SEL);

	/* Disable and clear rx idle counter before (re)configuration */
	wil_w(wil, RGF_DMA_ITR_RX_IDL_CNT_CTL, BIT_DMA_ITR_RX_IDL_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_RX_IDL_CNT_TRSH, wil->rx_interframe_timeout);
	wil_info(wil, "set ITR_RX_IDL_CNT_TRSH = %d usec\n",
		 wil->rx_interframe_timeout);
	/* Configure TX max burst duration timer to use usec units */
	wil_w(wil, RGF_DMA_ITR_RX_IDL_CNT_CTL, BIT_DMA_ITR_RX_IDL_CNT_CTL_EN |
	      BIT_DMA_ITR_RX_IDL_CNT_CTL_EXT_TIC_SEL);
}
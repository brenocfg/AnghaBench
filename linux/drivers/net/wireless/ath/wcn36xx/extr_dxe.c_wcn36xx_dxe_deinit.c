#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wcn36xx {int /*<<< orphan*/  dxe_rx_h_ch; int /*<<< orphan*/  dxe_rx_l_ch; int /*<<< orphan*/ * tx_ack_skb; int /*<<< orphan*/  hw; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wcn36xx*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dxe_ch_free_skbs (struct wcn36xx*,int /*<<< orphan*/ *) ; 

void wcn36xx_dxe_deinit(struct wcn36xx *wcn)
{
	free_irq(wcn->tx_irq, wcn);
	free_irq(wcn->rx_irq, wcn);

	if (wcn->tx_ack_skb) {
		ieee80211_tx_status_irqsafe(wcn->hw, wcn->tx_ack_skb);
		wcn->tx_ack_skb = NULL;
	}

	wcn36xx_dxe_ch_free_skbs(wcn, &wcn->dxe_rx_l_ch);
	wcn36xx_dxe_ch_free_skbs(wcn, &wcn->dxe_rx_h_ch);
}
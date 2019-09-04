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
struct net_device {int dummy; } ;
struct fec_enet_private {int quirks; scalar_t__ hwp; int /*<<< orphan*/  tx_time_itr; int /*<<< orphan*/  tx_pkts_itr; int /*<<< orphan*/  rx_time_itr; int /*<<< orphan*/  rx_pkts_itr; } ;

/* Variables and functions */
 int FEC_ITR_CLK_SEL ; 
 int FEC_ITR_EN ; 
 int FEC_ITR_ICFT (int /*<<< orphan*/ ) ; 
 int FEC_ITR_ICTT (int /*<<< orphan*/ ) ; 
 int FEC_QUIRK_HAS_AVB ; 
 scalar_t__ FEC_RXIC0 ; 
 scalar_t__ FEC_RXIC1 ; 
 scalar_t__ FEC_RXIC2 ; 
 scalar_t__ FEC_TXIC0 ; 
 scalar_t__ FEC_TXIC1 ; 
 scalar_t__ FEC_TXIC2 ; 
 int /*<<< orphan*/  fec_enet_us_to_itr_clock (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fec_enet_itr_coal_set(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int rx_itr, tx_itr;

	/* Must be greater than zero to avoid unpredictable behavior */
	if (!fep->rx_time_itr || !fep->rx_pkts_itr ||
	    !fep->tx_time_itr || !fep->tx_pkts_itr)
		return;

	/* Select enet system clock as Interrupt Coalescing
	 * timer Clock Source
	 */
	rx_itr = FEC_ITR_CLK_SEL;
	tx_itr = FEC_ITR_CLK_SEL;

	/* set ICFT and ICTT */
	rx_itr |= FEC_ITR_ICFT(fep->rx_pkts_itr);
	rx_itr |= FEC_ITR_ICTT(fec_enet_us_to_itr_clock(ndev, fep->rx_time_itr));
	tx_itr |= FEC_ITR_ICFT(fep->tx_pkts_itr);
	tx_itr |= FEC_ITR_ICTT(fec_enet_us_to_itr_clock(ndev, fep->tx_time_itr));

	rx_itr |= FEC_ITR_EN;
	tx_itr |= FEC_ITR_EN;

	writel(tx_itr, fep->hwp + FEC_TXIC0);
	writel(rx_itr, fep->hwp + FEC_RXIC0);
	if (fep->quirks & FEC_QUIRK_HAS_AVB) {
		writel(tx_itr, fep->hwp + FEC_TXIC1);
		writel(rx_itr, fep->hwp + FEC_RXIC1);
		writel(tx_itr, fep->hwp + FEC_TXIC2);
		writel(rx_itr, fep->hwp + FEC_RXIC2);
	}
}
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
struct net_device_stats {int rx_missed_errors; int rx_errors; int rx_crc_errors; int rx_frame_errors; int rx_over_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct arc_emac_priv {int rx_missed_errors; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int ERR_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int MDIO_MASK ; 
 unsigned int MSER_MASK ; 
 unsigned int RXCR_MASK ; 
 unsigned int RXFL_MASK ; 
 unsigned int RXFR_MASK ; 
 unsigned int RXINT_MASK ; 
 int /*<<< orphan*/  R_ENABLE ; 
 int /*<<< orphan*/  R_STATUS ; 
 unsigned int TXINT_MASK ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_reg_clr (struct arc_emac_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int arc_reg_get (struct arc_emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_reg_set (struct arc_emac_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t arc_emac_intr(int irq, void *dev_instance)
{
	struct net_device *ndev = dev_instance;
	struct arc_emac_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	unsigned int status;

	status = arc_reg_get(priv, R_STATUS);
	status &= ~MDIO_MASK;

	/* Reset all flags except "MDIO complete" */
	arc_reg_set(priv, R_STATUS, status);

	if (status & (RXINT_MASK | TXINT_MASK)) {
		if (likely(napi_schedule_prep(&priv->napi))) {
			arc_reg_clr(priv, R_ENABLE, RXINT_MASK | TXINT_MASK);
			__napi_schedule(&priv->napi);
		}
	}

	if (status & ERR_MASK) {
		/* MSER/RXCR/RXFR/RXFL interrupt fires on corresponding
		 * 8-bit error counter overrun.
		 */

		if (status & MSER_MASK) {
			stats->rx_missed_errors += 0x100;
			stats->rx_errors += 0x100;
			priv->rx_missed_errors += 0x100;
			napi_schedule(&priv->napi);
		}

		if (status & RXCR_MASK) {
			stats->rx_crc_errors += 0x100;
			stats->rx_errors += 0x100;
		}

		if (status & RXFR_MASK) {
			stats->rx_frame_errors += 0x100;
			stats->rx_errors += 0x100;
		}

		if (status & RXFL_MASK) {
			stats->rx_over_errors += 0x100;
			stats->rx_errors += 0x100;
		}
	}

	return IRQ_HANDLED;
}
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
typedef  int u32 ;
struct rcar_canfd_global {scalar_t__ fdmode; } ;
struct rcar_canfd_channel {int channel; int /*<<< orphan*/  base; struct rcar_canfd_global* gpriv; } ;
struct net_device_stats {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCANFD_CFFIFO_IDX ; 
 int /*<<< orphan*/  RCANFD_CFSTS (int,int /*<<< orphan*/ ) ; 
 int RCANFD_CFSTS_CFMLT ; 
 int /*<<< orphan*/  RCANFD_GERFL ; 
 int RCANFD_GERFL_CMPOF ; 
 int RCANFD_GERFL_EEF0 ; 
 int RCANFD_GERFL_EEF1 ; 
 int RCANFD_GERFL_MES ; 
 int RCANFD_RFFIFO_IDX ; 
 int /*<<< orphan*/  RCANFD_RFSTS (int) ; 
 int RCANFD_RFSTS_RFMLT ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct rcar_canfd_channel* netdev_priv (struct net_device*) ; 
 int rcar_canfd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_canfd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_canfd_global_error(struct net_device *ndev)
{
	struct rcar_canfd_channel *priv = netdev_priv(ndev);
	struct rcar_canfd_global *gpriv = priv->gpriv;
	struct net_device_stats *stats = &ndev->stats;
	u32 ch = priv->channel;
	u32 gerfl, sts;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	gerfl = rcar_canfd_read(priv->base, RCANFD_GERFL);
	if ((gerfl & RCANFD_GERFL_EEF0) && (ch == 0)) {
		netdev_dbg(ndev, "Ch0: ECC Error flag\n");
		stats->tx_dropped++;
	}
	if ((gerfl & RCANFD_GERFL_EEF1) && (ch == 1)) {
		netdev_dbg(ndev, "Ch1: ECC Error flag\n");
		stats->tx_dropped++;
	}
	if (gerfl & RCANFD_GERFL_MES) {
		sts = rcar_canfd_read(priv->base,
				      RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX));
		if (sts & RCANFD_CFSTS_CFMLT) {
			netdev_dbg(ndev, "Tx Message Lost flag\n");
			stats->tx_dropped++;
			rcar_canfd_write(priv->base,
					 RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX),
					 sts & ~RCANFD_CFSTS_CFMLT);
		}

		sts = rcar_canfd_read(priv->base, RCANFD_RFSTS(ridx));
		if (sts & RCANFD_RFSTS_RFMLT) {
			netdev_dbg(ndev, "Rx Message Lost flag\n");
			stats->rx_dropped++;
			rcar_canfd_write(priv->base, RCANFD_RFSTS(ridx),
					 sts & ~RCANFD_RFSTS_RFMLT);
		}
	}
	if (gpriv->fdmode && gerfl & RCANFD_GERFL_CMPOF) {
		/* Message Lost flag will be set for respective channel
		 * when this condition happens with counters and flags
		 * already updated.
		 */
		netdev_dbg(ndev, "global payload overflow interrupt\n");
	}

	/* Clear all global error interrupts. Only affected channels bits
	 * get cleared
	 */
	rcar_canfd_write(priv->base, RCANFD_GERFL, 0);
}
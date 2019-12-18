#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int mtu; int hard_header_len; } ;
struct TYPE_4__ {int tx_bytes; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; } ;
struct fza_private {int ring_rmc_txd_index; int ring_rmc_tx_index; int ring_rmc_tx_size; int /*<<< orphan*/  name; scalar_t__ queue_active; TYPE_2__ stats; TYPE_1__* ring_rmc_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  rmc; int /*<<< orphan*/  own; } ;

/* Variables and functions */
 int FZA_RING_OWN_MASK ; 
 int FZA_RING_PBC_MASK ; 
#define  FZA_RING_TX_DCC_ABORT 132 
#define  FZA_RING_TX_DCC_DTP 131 
#define  FZA_RING_TX_DCC_DTP_SOP 130 
 int FZA_RING_TX_DCC_MASK ; 
#define  FZA_RING_TX_DCC_PARITY 129 
 int FZA_RING_TX_DCC_SUCCESS ; 
#define  FZA_RING_TX_DCC_UNDRRUN 128 
 int FZA_RING_TX_OWN_RMC ; 
 int FZA_RING_TX_SOP ; 
 int FZA_TX_BUFFER_SIZE ; 
 struct fza_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int readl_o (int /*<<< orphan*/ *) ; 
 int readl_u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fza_tx(struct net_device *dev)
{
	struct fza_private *fp = netdev_priv(dev);
	u32 own, rmc;
	int i;

	while (1) {
		i = fp->ring_rmc_txd_index;
		if (i == fp->ring_rmc_tx_index)
			break;
		own = readl_o(&fp->ring_rmc_tx[i].own);
		if ((own & FZA_RING_OWN_MASK) == FZA_RING_TX_OWN_RMC)
			break;

		rmc = readl_u(&fp->ring_rmc_tx[i].rmc);
		/* Only process the first descriptor. */
		if ((rmc & FZA_RING_TX_SOP) != 0) {
			if ((rmc & FZA_RING_TX_DCC_MASK) ==
			    FZA_RING_TX_DCC_SUCCESS) {
				int pkt_len = (rmc & FZA_RING_PBC_MASK) - 3;
								/* Omit PRH. */

				fp->stats.tx_packets++;
				fp->stats.tx_bytes += pkt_len;
			} else {
				fp->stats.tx_errors++;
				switch (rmc & FZA_RING_TX_DCC_MASK) {
				case FZA_RING_TX_DCC_DTP_SOP:
				case FZA_RING_TX_DCC_DTP:
				case FZA_RING_TX_DCC_ABORT:
					fp->stats.tx_aborted_errors++;
					break;
				case FZA_RING_TX_DCC_UNDRRUN:
					fp->stats.tx_fifo_errors++;
					break;
				case FZA_RING_TX_DCC_PARITY:
				default:
					break;
				}
			}
		}

		fp->ring_rmc_txd_index = (fp->ring_rmc_txd_index + 1) %
					 fp->ring_rmc_tx_size;
	}

	if (((((fp->ring_rmc_txd_index - 1 + fp->ring_rmc_tx_size) -
	       fp->ring_rmc_tx_index) % fp->ring_rmc_tx_size) *
	     FZA_TX_BUFFER_SIZE) >= dev->mtu + dev->hard_header_len) {
		if (fp->queue_active) {
			netif_wake_queue(dev);
			pr_debug("%s: queue woken\n", fp->name);
		}
	}
}
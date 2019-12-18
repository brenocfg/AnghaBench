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
struct net_device {int dummy; } ;
struct fec_enet_private {int num_rx_queues; int num_tx_queues; scalar_t__ hwp; struct fec_enet_priv_tx_q** tx_queue; struct fec_enet_priv_rx_q** rx_queue; } ;
struct TYPE_4__ {int dma; } ;
struct fec_enet_priv_tx_q {TYPE_2__ bd; } ;
struct TYPE_3__ {int dma; } ;
struct fec_enet_priv_rx_q {TYPE_1__ bd; } ;

/* Variables and functions */
 int DMA_CLASS_EN ; 
 scalar_t__ FEC_DMA_CFG (int) ; 
 scalar_t__ FEC_RCMR (int) ; 
 scalar_t__ FEC_R_BUFF_SIZE (int) ; 
 scalar_t__ FEC_R_DES_START (int) ; 
 scalar_t__ FEC_X_DES_START (int) ; 
 int IDLE_SLOPE (int) ; 
 int PKT_MAXBUF_SIZE ; 
 int RCMR_CMP (int) ; 
 int RCMR_MATCHEN ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fec_enet_enable_ring(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_enet_priv_tx_q *txq;
	struct fec_enet_priv_rx_q *rxq;
	int i;

	for (i = 0; i < fep->num_rx_queues; i++) {
		rxq = fep->rx_queue[i];
		writel(rxq->bd.dma, fep->hwp + FEC_R_DES_START(i));
		writel(PKT_MAXBUF_SIZE, fep->hwp + FEC_R_BUFF_SIZE(i));

		/* enable DMA1/2 */
		if (i)
			writel(RCMR_MATCHEN | RCMR_CMP(i),
			       fep->hwp + FEC_RCMR(i));
	}

	for (i = 0; i < fep->num_tx_queues; i++) {
		txq = fep->tx_queue[i];
		writel(txq->bd.dma, fep->hwp + FEC_X_DES_START(i));

		/* enable DMA1/2 */
		if (i)
			writel(DMA_CLASS_EN | IDLE_SLOPE(i),
			       fep->hwp + FEC_DMA_CFG(i));
	}
}
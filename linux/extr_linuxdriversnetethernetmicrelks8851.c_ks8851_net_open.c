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
struct ks8851_net {int rc_rxqcr; int rc_ier; int /*<<< orphan*/  lock; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRR_QMU ; 
 int IRQ_LCI ; 
 int IRQ_RXI ; 
 int IRQ_RXPSI ; 
 int IRQ_SPIBEI ; 
 int IRQ_TXI ; 
 int IRQ_TXPSI ; 
 int /*<<< orphan*/  KS_IER ; 
 int /*<<< orphan*/  KS_ISR ; 
 int /*<<< orphan*/  KS_RXCR1 ; 
 int /*<<< orphan*/  KS_RXCR2 ; 
 int /*<<< orphan*/  KS_RXDBCTR ; 
 int /*<<< orphan*/  KS_RXDTTR ; 
 int /*<<< orphan*/  KS_RXFCTR ; 
 int /*<<< orphan*/  KS_RXQCR ; 
 int /*<<< orphan*/  KS_TXCR ; 
 int /*<<< orphan*/  KS_TXFDPR ; 
 int /*<<< orphan*/  PMECR_PM_NORMAL ; 
 int RXCR1_RXBE ; 
 int RXCR1_RXE ; 
 int RXCR1_RXFCE ; 
 int RXCR1_RXPAFMA ; 
 int RXCR1_RXUE ; 
 int RXCR2_SRDBL_FRAME ; 
 int RXQCR_RXDBCTE ; 
 int RXQCR_RXDTTE ; 
 int RXQCR_RXFCTE ; 
 int TXCR_TXCRC ; 
 int TXCR_TXE ; 
 int TXCR_TXFCE ; 
 int TXCR_TXPE ; 
 int TXFDPR_TXFPAI ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  ks8851_set_powermode (struct ks8851_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8851_soft_reset (struct ks8851_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8851_wrreg16 (struct ks8851_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks8851_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ks8851_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks8851_net_open(struct net_device *dev)
{
	struct ks8851_net *ks = netdev_priv(dev);

	/* lock the card, even if we may not actually be doing anything
	 * else at the moment */
	mutex_lock(&ks->lock);

	netif_dbg(ks, ifup, ks->netdev, "opening\n");

	/* bring chip out of any power saving mode it was in */
	ks8851_set_powermode(ks, PMECR_PM_NORMAL);

	/* issue a soft reset to the RX/TX QMU to put it into a known
	 * state. */
	ks8851_soft_reset(ks, GRR_QMU);

	/* setup transmission parameters */

	ks8851_wrreg16(ks, KS_TXCR, (TXCR_TXE | /* enable transmit process */
				     TXCR_TXPE | /* pad to min length */
				     TXCR_TXCRC | /* add CRC */
				     TXCR_TXFCE)); /* enable flow control */

	/* auto-increment tx data, reset tx pointer */
	ks8851_wrreg16(ks, KS_TXFDPR, TXFDPR_TXFPAI);

	/* setup receiver control */

	ks8851_wrreg16(ks, KS_RXCR1, (RXCR1_RXPAFMA | /*  from mac filter */
				      RXCR1_RXFCE | /* enable flow control */
				      RXCR1_RXBE | /* broadcast enable */
				      RXCR1_RXUE | /* unicast enable */
				      RXCR1_RXE)); /* enable rx block */

	/* transfer entire frames out in one go */
	ks8851_wrreg16(ks, KS_RXCR2, RXCR2_SRDBL_FRAME);

	/* set receive counter timeouts */
	ks8851_wrreg16(ks, KS_RXDTTR, 1000); /* 1ms after first frame to IRQ */
	ks8851_wrreg16(ks, KS_RXDBCTR, 4096); /* >4Kbytes in buffer to IRQ */
	ks8851_wrreg16(ks, KS_RXFCTR, 10);  /* 10 frames to IRQ */

	ks->rc_rxqcr = (RXQCR_RXFCTE |  /* IRQ on frame count exceeded */
			RXQCR_RXDBCTE | /* IRQ on byte count exceeded */
			RXQCR_RXDTTE);  /* IRQ on time exceeded */

	ks8851_wrreg16(ks, KS_RXQCR, ks->rc_rxqcr);

	/* clear then enable interrupts */

#define STD_IRQ (IRQ_LCI |	/* Link Change */	\
		 IRQ_TXI |	/* TX done */		\
		 IRQ_RXI |	/* RX done */		\
		 IRQ_SPIBEI |	/* SPI bus error */	\
		 IRQ_TXPSI |	/* TX process stop */	\
		 IRQ_RXPSI)	/* RX process stop */

	ks->rc_ier = STD_IRQ;
	ks8851_wrreg16(ks, KS_ISR, STD_IRQ);
	ks8851_wrreg16(ks, KS_IER, STD_IRQ);

	netif_start_queue(ks->netdev);

	netif_dbg(ks, ifup, ks->netdev, "network device up\n");

	mutex_unlock(&ks->lock);
	return 0;
}
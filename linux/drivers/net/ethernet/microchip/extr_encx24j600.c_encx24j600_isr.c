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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct encx24j600_priv {int /*<<< orphan*/  lock; struct net_device* ndev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLREIE ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  ESTAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LINKIF ; 
 int PCFULIF ; 
 int PKTIF ; 
 int RXABTIF ; 
 int /*<<< orphan*/  SETEIE ; 
 int TXABTIF ; 
 int TXIF ; 
 int /*<<< orphan*/  encx24j600_clr_bits (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  encx24j600_cmd (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_int_link_handler (struct encx24j600_priv*) ; 
 int encx24j600_read_reg (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_rx_packets (struct encx24j600_priv*,int) ; 
 int /*<<< orphan*/  encx24j600_tx_complete (struct encx24j600_priv*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct encx24j600_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static irqreturn_t encx24j600_isr(int irq, void *dev_id)
{
	struct encx24j600_priv *priv = dev_id;
	struct net_device *dev = priv->ndev;
	int eir;

	/* Clear interrupts */
	encx24j600_cmd(priv, CLREIE);

	eir = encx24j600_read_reg(priv, EIR);

	if (eir & LINKIF)
		encx24j600_int_link_handler(priv);

	if (eir & TXIF)
		encx24j600_tx_complete(priv, false);

	if (eir & TXABTIF)
		encx24j600_tx_complete(priv, true);

	if (eir & RXABTIF) {
		if (eir & PCFULIF) {
			/* Packet counter is full */
			netif_err(priv, rx_err, dev, "Packet counter full\n");
		}
		dev->stats.rx_dropped++;
		encx24j600_clr_bits(priv, EIR, RXABTIF);
	}

	if (eir & PKTIF) {
		u8 packet_count;

		mutex_lock(&priv->lock);

		packet_count = encx24j600_read_reg(priv, ESTAT) & 0xff;
		while (packet_count) {
			encx24j600_rx_packets(priv, packet_count);
			packet_count = encx24j600_read_reg(priv, ESTAT) & 0xff;
		}

		mutex_unlock(&priv->lock);
	}

	/* Enable interrupts */
	encx24j600_cmd(priv, SETEIE);

	return IRQ_HANDLED;
}
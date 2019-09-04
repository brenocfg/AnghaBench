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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct encx24j600_priv {TYPE_1__* tx_skb; struct net_device* ndev; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGPWRPT ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  ENC_TX_BUF_START ; 
 int /*<<< orphan*/  ETXLEN ; 
 int /*<<< orphan*/  ETXST ; 
 int /*<<< orphan*/  SETTXRTS ; 
 int TXABTIF ; 
 int /*<<< orphan*/  TXIF ; 
 int /*<<< orphan*/  WGPDATA ; 
 int /*<<< orphan*/  dump_packet (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  encx24j600_clr_bits (struct encx24j600_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_cmd (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_raw_write (struct encx24j600_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int encx24j600_read_reg (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_reset_hw_tx (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct encx24j600_priv*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_pktdata (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  tx_queued ; 

__attribute__((used)) static void encx24j600_hw_tx(struct encx24j600_priv *priv)
{
	struct net_device *dev = priv->ndev;

	netif_info(priv, tx_queued, dev, "TX Packet Len:%d\n",
		   priv->tx_skb->len);

	if (netif_msg_pktdata(priv))
		dump_packet("TX", priv->tx_skb->len, priv->tx_skb->data);

	if (encx24j600_read_reg(priv, EIR) & TXABTIF)
		/* Last transmition aborted due to error. Reset TX interface */
		encx24j600_reset_hw_tx(priv);

	/* Clear the TXIF flag if were previously set */
	encx24j600_clr_bits(priv, EIR, TXIF);

	/* Set the data pointer to the TX buffer address in the SRAM */
	encx24j600_write_reg(priv, EGPWRPT, ENC_TX_BUF_START);

	/* Copy the packet into the SRAM */
	encx24j600_raw_write(priv, WGPDATA, (u8 *)priv->tx_skb->data,
			     priv->tx_skb->len);

	/* Program the Tx buffer start pointer */
	encx24j600_write_reg(priv, ETXST, ENC_TX_BUF_START);

	/* Program the packet length */
	encx24j600_write_reg(priv, ETXLEN, priv->tx_skb->len);

	/* Start the transmission */
	encx24j600_cmd(priv, SETTXRTS);
}
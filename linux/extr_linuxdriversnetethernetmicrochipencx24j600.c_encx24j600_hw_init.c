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
typedef  int u16 ;
struct encx24j600_priv {int hw_enabled; scalar_t__ autoneg; int /*<<< orphan*/  rxfilter; scalar_t__ full_duplex; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  EIDLED ; 
 int FULDPX ; 
 int /*<<< orphan*/  MACON1 ; 
 int /*<<< orphan*/  MACON2 ; 
 int MACON2_DEFER ; 
 int MACON2_RSV1 ; 
 int /*<<< orphan*/  MAIPG ; 
 int /*<<< orphan*/  MAMXFL ; 
 int MAX_FRAMELEN ; 
 int PADCFG0 ; 
 int PADCFG2 ; 
 int /*<<< orphan*/  PHANA ; 
 int /*<<< orphan*/  PHANA_DEFAULT ; 
 int /*<<< orphan*/  RXFILTER_NORMAL ; 
 int TXCRCEN ; 
 int /*<<< orphan*/  encx24j600_check_link_status (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_dump_config (struct encx24j600_priv*,char*) ; 
 int /*<<< orphan*/  encx24j600_hw_init_rx (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_hw_init_tx (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_set_bits (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  encx24j600_set_rxfilter_mode (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_update_phcon1 (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_update_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  encx24j600_write_phy (struct encx24j600_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_msg_hw (struct encx24j600_priv*) ; 

__attribute__((used)) static int encx24j600_hw_init(struct encx24j600_priv *priv)
{
	int ret = 0;
	u16 macon2;

	priv->hw_enabled = false;

	/* PHY Leds: link status,
	 * LEDA: Link State + collision events
	 * LEDB: Link State + transmit/receive events
	 */
	encx24j600_update_reg(priv, EIDLED, 0xff00, 0xcb00);

	/* Loopback disabled */
	encx24j600_write_reg(priv, MACON1, 0x9);

	/* interpacket gap value */
	encx24j600_write_reg(priv, MAIPG, 0x0c12);

	/* Write the auto negotiation pattern */
	encx24j600_write_phy(priv, PHANA, PHANA_DEFAULT);

	encx24j600_update_phcon1(priv);
	encx24j600_check_link_status(priv);

	macon2 = MACON2_RSV1 | TXCRCEN | PADCFG0 | PADCFG2 | MACON2_DEFER;
	if ((priv->autoneg == AUTONEG_DISABLE) && priv->full_duplex)
		macon2 |= FULDPX;

	encx24j600_set_bits(priv, MACON2, macon2);

	priv->rxfilter = RXFILTER_NORMAL;
	encx24j600_set_rxfilter_mode(priv);

	/* Program the Maximum frame length */
	encx24j600_write_reg(priv, MAMXFL, MAX_FRAMELEN);

	/* Init Tx pointers */
	encx24j600_hw_init_tx(priv);

	/* Init Rx pointers */
	encx24j600_hw_init_rx(priv);

	if (netif_msg_hw(priv))
		encx24j600_dump_config(priv, "Hw is initialized");

	return ret;
}
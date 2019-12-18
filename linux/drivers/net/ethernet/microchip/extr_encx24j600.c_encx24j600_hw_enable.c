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
struct encx24j600_priv {int hw_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIE ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  ENABLERX ; 
 int INTIE ; 
 int LINKIE ; 
 int LINKIF ; 
 int PCFULIE ; 
 int PCFULIF ; 
 int PKTIE ; 
 int PKTIF ; 
 int RXABTIE ; 
 int RXABTIF ; 
 int TXABTIE ; 
 int TXABTIF ; 
 int TXIE ; 
 int TXIF ; 
 int /*<<< orphan*/  encx24j600_clr_bits (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  encx24j600_cmd (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encx24j600_hw_enable(struct encx24j600_priv *priv)
{
	/* Clear the interrupt flags in case was set */
	encx24j600_clr_bits(priv, EIR, (PCFULIF | RXABTIF | TXABTIF | TXIF |
					PKTIF | LINKIF));

	/* Enable the interrupts */
	encx24j600_write_reg(priv, EIE, (PCFULIE | RXABTIE | TXABTIE | TXIE |
					 PKTIE | LINKIE | INTIE));

	/* Enable RX */
	encx24j600_cmd(priv, ENABLERX);

	priv->hw_enabled = true;
}
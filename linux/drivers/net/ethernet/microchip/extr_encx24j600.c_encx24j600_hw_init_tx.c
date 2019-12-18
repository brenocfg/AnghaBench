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
struct encx24j600_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGPWRPT ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  ENC_TX_BUF_START ; 
 int TXABTIF ; 
 int TXIF ; 
 int /*<<< orphan*/  encx24j600_clr_bits (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  encx24j600_reset_hw_tx (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encx24j600_hw_init_tx(struct encx24j600_priv *priv)
{
	/* Reset TX */
	encx24j600_reset_hw_tx(priv);

	/* Clear the TXIF flag if were previously set */
	encx24j600_clr_bits(priv, EIR, TXIF | TXABTIF);

	/* Write the Tx Buffer pointer */
	encx24j600_write_reg(priv, EGPWRPT, ENC_TX_BUF_START);
}
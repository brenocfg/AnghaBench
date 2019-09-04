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
struct encx24j600_priv {scalar_t__ next_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLERX ; 
 scalar_t__ ENC_RX_BUF_START ; 
 scalar_t__ ENC_SRAM_SIZE ; 
 int /*<<< orphan*/  ERXRDPT ; 
 int /*<<< orphan*/  ERXST ; 
 int /*<<< orphan*/  ERXTAIL ; 
 int /*<<< orphan*/  EUDAND ; 
 int /*<<< orphan*/  EUDAST ; 
 int /*<<< orphan*/  MAMXFL ; 
 scalar_t__ MAX_FRAMELEN ; 
 int /*<<< orphan*/  encx24j600_cmd (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void encx24j600_hw_init_rx(struct encx24j600_priv *priv)
{
	encx24j600_cmd(priv, DISABLERX);

	/* Set up RX packet start address in the SRAM */
	encx24j600_write_reg(priv, ERXST, ENC_RX_BUF_START);

	/* Preload the RX Data pointer to the beginning of the RX area */
	encx24j600_write_reg(priv, ERXRDPT, ENC_RX_BUF_START);

	priv->next_packet = ENC_RX_BUF_START;

	/* Set up RX end address in the SRAM */
	encx24j600_write_reg(priv, ERXTAIL, ENC_SRAM_SIZE - 2);

	/* Reset the  user data pointers    */
	encx24j600_write_reg(priv, EUDAST, ENC_SRAM_SIZE);
	encx24j600_write_reg(priv, EUDAND, ENC_SRAM_SIZE + 1);

	/* Set Max Frame length */
	encx24j600_write_reg(priv, MAMXFL, MAX_FRAMELEN);
}
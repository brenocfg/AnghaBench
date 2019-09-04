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
struct sii9234 {int /*<<< orphan*/  dev; } ;
typedef  enum sii9234_state { ____Placeholder_sii9234_state } sii9234_state ;

/* Variables and functions */
 int HPD_CHANGE_INT_MASK ; 
 int /*<<< orphan*/  MHL_TX_DISC_CTRL1_REG ; 
 int /*<<< orphan*/  MHL_TX_INTR1_ENABLE_REG ; 
 int /*<<< orphan*/  MHL_TX_MHLTX_CTL1_REG ; 
 int RSEN_CHANGE_INT_MASK ; 
 int ST_FAILURE ; 
 int ST_MHL_ESTABLISHED ; 
 int /*<<< orphan*/  cbus_writeb (struct sii9234*,int,int) ; 
 int /*<<< orphan*/  cbus_writebm (struct sii9234*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mhl_tx_writeb (struct sii9234*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mhl_tx_writebm (struct sii9234*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sii9234_clear_error (struct sii9234*) ; 

__attribute__((used)) static enum sii9234_state sii9234_mhl_established(struct sii9234 *ctx)
{
	dev_dbg(ctx->dev, "mhl est interrupt\n");

	/* Discovery override */
	mhl_tx_writeb(ctx, MHL_TX_MHLTX_CTL1_REG, 0x10);
	/* Increase DDC translation layer timer (byte mode) */
	cbus_writeb(ctx, 0x07, 0x32);
	cbus_writebm(ctx, 0x44, ~0, 1 << 1);
	/* Keep the discovery enabled. Need RGND interrupt */
	mhl_tx_writebm(ctx, MHL_TX_DISC_CTRL1_REG, ~0, 1);
	mhl_tx_writeb(ctx, MHL_TX_INTR1_ENABLE_REG,
		      RSEN_CHANGE_INT_MASK | HPD_CHANGE_INT_MASK);

	if (sii9234_clear_error(ctx))
		return ST_FAILURE;

	return ST_MHL_ESTABLISHED;
}
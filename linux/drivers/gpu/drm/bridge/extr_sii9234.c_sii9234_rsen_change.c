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
struct sii9234 {scalar_t__ state; int /*<<< orphan*/  dev; } ;
typedef  enum sii9234_state { ____Placeholder_sii9234_state } sii9234_state ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_TX_SYSSTAT_REG ; 
 int RSEN_STATUS ; 
 int ST_FAILURE ; 
 scalar_t__ ST_RGND_1K ; 
 int ST_RSEN_HIGH ; 
 int /*<<< orphan*/  T_SRC_RXSENSE_DEGLITCH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  force_usb_id_switch_open (struct sii9234*) ; 
 int mhl_tx_readb (struct sii9234*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_usb_id_switch_open (struct sii9234*) ; 
 int /*<<< orphan*/  sii9234_tmds_control (struct sii9234*,int) ; 

__attribute__((used)) static enum sii9234_state sii9234_rsen_change(struct sii9234 *ctx)
{
	int value;

	/* Work_around code to handle wrong interrupt */
	if (ctx->state != ST_RGND_1K) {
		dev_err(ctx->dev, "RSEN_HIGH without RGND_1K\n");
		return ST_FAILURE;
	}
	value = mhl_tx_readb(ctx, MHL_TX_SYSSTAT_REG);
	if (value < 0)
		return ST_FAILURE;

	if (value & RSEN_STATUS) {
		dev_dbg(ctx->dev, "MHL cable connected.. RSEN High\n");
		return ST_RSEN_HIGH;
	}
	dev_dbg(ctx->dev, "RSEN lost\n");
	/*
	 * Once RSEN loss is confirmed,we need to check
	 * based on cable status and chip power status,whether
	 * it is SINK Loss(HDMI cable not connected, TV Off)
	 * or MHL cable disconnection
	 * TODO: Define the below mhl_disconnection()
	 */
	msleep(T_SRC_RXSENSE_DEGLITCH);
	value = mhl_tx_readb(ctx, MHL_TX_SYSSTAT_REG);
	if (value < 0)
		return ST_FAILURE;
	dev_dbg(ctx->dev, "sys_stat: %x\n", value);

	if (value & RSEN_STATUS) {
		dev_dbg(ctx->dev, "RSEN recovery\n");
		return ST_RSEN_HIGH;
	}
	dev_dbg(ctx->dev, "RSEN Really LOW\n");
	/* To meet CTS 3.3.22.2 spec */
	sii9234_tmds_control(ctx, false);
	force_usb_id_switch_open(ctx);
	release_usb_id_switch_open(ctx);

	return ST_FAILURE;
}
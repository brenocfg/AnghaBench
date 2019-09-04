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
typedef  int /*<<< orphan*/  u32 ;
struct slimpro_i2c_dev {int /*<<< orphan*/ * resp_msg; int /*<<< orphan*/  mbox_chan; int /*<<< orphan*/  rd_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_disabled ; 
 int /*<<< orphan*/  mbox_chan_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slimpro_i2c_pcc_tx_prepare (struct slimpro_i2c_dev*,int /*<<< orphan*/ *) ; 
 int start_i2c_msg_xfer (struct slimpro_i2c_dev*) ; 

__attribute__((used)) static int slimpro_i2c_send_msg(struct slimpro_i2c_dev *ctx,
				u32 *msg,
				u32 *data)
{
	int rc;

	ctx->resp_msg = data;

	if (!acpi_disabled) {
		reinit_completion(&ctx->rd_complete);
		slimpro_i2c_pcc_tx_prepare(ctx, msg);
	}

	rc = mbox_send_message(ctx->mbox_chan, msg);
	if (rc < 0)
		goto err;

	rc = start_i2c_msg_xfer(ctx);

err:
	if (!acpi_disabled)
		mbox_chan_txdone(ctx->mbox_chan, 0);

	ctx->resp_msg = NULL;

	return rc;
}
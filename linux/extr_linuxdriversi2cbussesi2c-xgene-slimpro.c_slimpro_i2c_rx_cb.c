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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ tx_block; } ;
struct slimpro_i2c_dev {int /*<<< orphan*/  rd_complete; TYPE_1__ mbox_client; int /*<<< orphan*/ * resp_msg; } ;
struct mbox_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct slimpro_i2c_dev* to_slimpro_i2c_dev (struct mbox_client*) ; 

__attribute__((used)) static void slimpro_i2c_rx_cb(struct mbox_client *cl, void *mssg)
{
	struct slimpro_i2c_dev *ctx = to_slimpro_i2c_dev(cl);

	/*
	 * Response message format:
	 * mssg[0] is the return code of the operation
	 * mssg[1] is the first data word
	 * mssg[2] is NOT used
	 */
	if (ctx->resp_msg)
		*ctx->resp_msg = ((u32 *)mssg)[1];

	if (ctx->mbox_client.tx_block)
		complete(&ctx->rd_complete);
}
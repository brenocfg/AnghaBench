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
struct TYPE_2__ {scalar_t__ tx_block; } ;
struct slimpro_i2c_dev {int* resp_msg; int /*<<< orphan*/  rd_complete; TYPE_1__ mbox_client; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MAILBOX_OP_TIMEOUT ; 
 int /*<<< orphan*/  acpi_disabled ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_i2c_msg_xfer(struct slimpro_i2c_dev *ctx)
{
	if (ctx->mbox_client.tx_block || !acpi_disabled) {
		if (!wait_for_completion_timeout(&ctx->rd_complete,
						 msecs_to_jiffies(MAILBOX_OP_TIMEOUT)))
			return -ETIMEDOUT;
	}

	/* Check of invalid data or no device */
	if (*ctx->resp_msg == 0xffffffff)
		return -ENODEV;

	return 0;
}
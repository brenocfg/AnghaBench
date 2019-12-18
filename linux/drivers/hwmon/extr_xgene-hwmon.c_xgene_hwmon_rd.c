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
struct TYPE_2__ {int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  msg; } ;
struct xgene_hwmon_dev {int resp_pending; int /*<<< orphan*/  rd_mutex; TYPE_1__ sync_msg; int /*<<< orphan*/  dev; int /*<<< orphan*/  rd_complete; int /*<<< orphan*/  mbox_chan; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MBOX_OP_TIMEOUTMS ; 
 scalar_t__ MSG_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ MSG_TYPE_ERR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_hwmon_rd(struct xgene_hwmon_dev *ctx, u32 *msg)
{
	int rc;

	mutex_lock(&ctx->rd_mutex);
	init_completion(&ctx->rd_complete);
	ctx->resp_pending = true;

	rc = mbox_send_message(ctx->mbox_chan, msg);
	if (rc < 0) {
		dev_err(ctx->dev, "Mailbox send error %d\n", rc);
		goto err;
	}

	if (!wait_for_completion_timeout(&ctx->rd_complete,
					 msecs_to_jiffies(MBOX_OP_TIMEOUTMS))) {
		dev_err(ctx->dev, "Mailbox operation timed out\n");
		rc = -ETIMEDOUT;
		goto err;
	}

	/* Check for error message */
	if (MSG_TYPE(ctx->sync_msg.msg) == MSG_TYPE_ERR) {
		rc = -EINVAL;
		goto err;
	}

	msg[0] = ctx->sync_msg.msg;
	msg[1] = ctx->sync_msg.param1;
	msg[2] = ctx->sync_msg.param2;

err:
	ctx->resp_pending = false;
	mutex_unlock(&ctx->rd_mutex);
	return rc;
}
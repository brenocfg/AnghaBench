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
struct rpmsg_device {int /*<<< orphan*/  ept; } ;
struct delta_ipc_ctx {int cb_err; int /*<<< orphan*/  done; int /*<<< orphan*/ * ipc_buf; } ;
struct delta_ipc_close_msg {int /*<<< orphan*/  header; } ;
struct delta_dev {int /*<<< orphan*/  dev; struct rpmsg_device* rpmsg_device; } ;
struct delta_ctx {int /*<<< orphan*/  sys_errors; int /*<<< orphan*/  name; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_IPC_CLOSE ; 
 int /*<<< orphan*/  IPC_TIMEOUT ; 
 int /*<<< orphan*/  build_msg_header (struct delta_ipc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  hw_free (struct delta_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int rpmsg_send (int /*<<< orphan*/ ,struct delta_ipc_close_msg*,int) ; 
 struct delta_ipc_ctx* to_ctx (void*) ; 
 struct delta_ctx* to_pctx (struct delta_ipc_ctx*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void delta_ipc_close(void *hdl)
{
	struct delta_ipc_ctx *ctx = to_ctx(hdl);
	struct delta_ctx *pctx = to_pctx(ctx);
	struct delta_dev *delta = pctx->dev;
	struct rpmsg_device *rpmsg_device = delta->rpmsg_device;
	struct delta_ipc_close_msg msg;
	int ret;

	if (!hdl) {
		dev_err(delta->dev,
			"%s   ipc: failed to close, invalid ipc handle\n",
			pctx->name);
		return;
	}

	if (ctx->ipc_buf) {
		hw_free(pctx, ctx->ipc_buf);
		ctx->ipc_buf = NULL;
	}

	if (!rpmsg_device) {
		dev_err(delta->dev,
			"%s   ipc: failed to close, rpmsg is not initialized\n",
			pctx->name);
		return;
	}

	/* build rpmsg message */
	build_msg_header(ctx, DELTA_IPC_CLOSE, &msg.header);

	/* send it */
	ret = rpmsg_send(rpmsg_device->ept, &msg, sizeof(msg));
	if (ret) {
		dev_err(delta->dev,
			"%s   ipc: failed to close, rpmsg_send failed (%d) for DELTA_IPC_CLOSE\n",
			pctx->name, ret);
		pctx->sys_errors++;
		return;
	}

	/* wait for acknowledge */
	if (!wait_for_completion_timeout
	    (&ctx->done, msecs_to_jiffies(IPC_TIMEOUT))) {
		dev_err(delta->dev,
			"%s   ipc: failed to close, timeout waiting for DELTA_IPC_CLOSE callback\n",
			pctx->name);
		pctx->sys_errors++;
		return;
	}

	/* command completed, check status */
	if (ctx->cb_err) {
		dev_err(delta->dev,
			"%s   ipc: failed to close, DELTA_IPC_CLOSE completed but with error (%d)\n",
			pctx->name, ctx->cb_err);
		pctx->sys_errors++;
	}
}
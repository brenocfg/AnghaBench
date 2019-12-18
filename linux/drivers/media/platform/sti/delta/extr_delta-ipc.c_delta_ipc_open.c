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
typedef  scalar_t__ u32 ;
struct rpmsg_device {int /*<<< orphan*/  ept; } ;
struct delta_ipc_param {char const* data; scalar_t__ size; } ;
struct delta_ipc_open_msg {int param_size; int /*<<< orphan*/  param_paddr; scalar_t__* name; int /*<<< orphan*/  ipc_buf_paddr; scalar_t__ ipc_buf_size; int /*<<< orphan*/  header; } ;
struct delta_buf {int /*<<< orphan*/  paddr; scalar_t__* vaddr; int /*<<< orphan*/  size; } ;
struct delta_ipc_ctx {int cb_err; struct delta_buf* ipc_buf; int /*<<< orphan*/  done; struct delta_buf ipc_buf_struct; } ;
struct delta_dev {int /*<<< orphan*/  dev; struct rpmsg_device* rpmsg_device; } ;
struct delta_ctx {int /*<<< orphan*/  sys_errors; int /*<<< orphan*/  name; struct delta_ipc_ctx ipc_ctx; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_IPC_OPEN ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPC_TIMEOUT ; 
 int /*<<< orphan*/  build_msg_header (struct delta_ipc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int hw_alloc (struct delta_ctx*,scalar_t__,char*,struct delta_buf*) ; 
 int /*<<< orphan*/  hw_free (struct delta_ctx*,struct delta_buf*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int rpmsg_send (int /*<<< orphan*/ ,struct delta_ipc_open_msg*,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int delta_ipc_open(struct delta_ctx *pctx, const char *name,
		   struct delta_ipc_param *param, u32 ipc_buf_size,
		   struct delta_buf **ipc_buf, void **hdl)
{
	struct delta_dev *delta = pctx->dev;
	struct rpmsg_device *rpmsg_device = delta->rpmsg_device;
	struct delta_ipc_ctx *ctx = &pctx->ipc_ctx;
	struct delta_ipc_open_msg msg;
	struct delta_buf *buf = &ctx->ipc_buf_struct;
	int ret;

	if (!rpmsg_device) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, rpmsg is not initialized\n",
			pctx->name);
		pctx->sys_errors++;
		return -EINVAL;
	}

	if (!name) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, no name given\n",
			pctx->name);
		return -EINVAL;
	}

	if (!param || !param->data || !param->size) {
		dev_err(delta->dev,
			"%s  ipc: failed to open, empty parameter\n",
			pctx->name);
		return -EINVAL;
	}

	if (!ipc_buf_size) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, no size given for ipc buffer\n",
			pctx->name);
		return -EINVAL;
	}

	if (param->size > ipc_buf_size) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, too large ipc parameter (%d bytes while max %d expected)\n",
			pctx->name,
			param->size, ctx->ipc_buf->size);
		return -EINVAL;
	}

	/* init */
	init_completion(&ctx->done);

	/*
	 * allocation of contiguous buffer for
	 * data of commands exchanged between
	 * host and firmware coprocessor
	 */
	ret = hw_alloc(pctx, ipc_buf_size,
		       "ipc data buffer", buf);
	if (ret)
		return ret;
	ctx->ipc_buf = buf;

	/* build rpmsg message */
	build_msg_header(ctx, DELTA_IPC_OPEN, &msg.header);

	msg.ipc_buf_size = ipc_buf_size;
	msg.ipc_buf_paddr = ctx->ipc_buf->paddr;

	memcpy(msg.name, name, sizeof(msg.name));
	msg.name[sizeof(msg.name) - 1] = 0;

	msg.param_size = param->size;
	memcpy(ctx->ipc_buf->vaddr, param->data, msg.param_size);
	msg.param_paddr = ctx->ipc_buf->paddr;

	/* send it */
	ret = rpmsg_send(rpmsg_device->ept, &msg, sizeof(msg));
	if (ret) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, rpmsg_send failed (%d) for DELTA_IPC_OPEN (name=%s, size=%d, data=%p)\n",
			pctx->name,
			ret, name, param->size, param->data);
		goto err;
	}

	/* wait for acknowledge */
	if (!wait_for_completion_timeout
	    (&ctx->done, msecs_to_jiffies(IPC_TIMEOUT))) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, timeout waiting for DELTA_IPC_OPEN callback (name=%s, size=%d, data=%p)\n",
			pctx->name,
			name, param->size, param->data);
		ret = -ETIMEDOUT;
		goto err;
	}

	/* command completed, check error */
	if (ctx->cb_err) {
		dev_err(delta->dev,
			"%s   ipc: failed to open, DELTA_IPC_OPEN completed but with error (%d) (name=%s, size=%d, data=%p)\n",
			pctx->name,
			ctx->cb_err, name, param->size, param->data);
		ret = -EIO;
		goto err;
	}

	*ipc_buf = ctx->ipc_buf;
	*hdl = (void *)ctx;

	return 0;

err:
	pctx->sys_errors++;
	hw_free(pctx, ctx->ipc_buf);
	ctx->ipc_buf = NULL;

	return ret;
}
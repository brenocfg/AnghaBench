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
struct dvb_vb2_ctx {scalar_t__ buf_siz; int /*<<< orphan*/  buf_cnt; int /*<<< orphan*/  name; int /*<<< orphan*/  state; int /*<<< orphan*/  vb_q; } ;
struct dmx_requestbuffers {scalar_t__ size; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ DVB_V2_MAX_SIZE ; 
 int /*<<< orphan*/  DVB_VB2_STATE_NONE ; 
 int /*<<< orphan*/  DVB_VB2_STATE_REQBUFS ; 
 int /*<<< orphan*/  VB2_MEMORY_MMAP ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int vb2_core_reqbufs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dvb_vb2_reqbufs(struct dvb_vb2_ctx *ctx, struct dmx_requestbuffers *req)
{
	int ret;

	/* Adjust size to a sane value */
	if (req->size > DVB_V2_MAX_SIZE)
		req->size = DVB_V2_MAX_SIZE;

	/* FIXME: round req->size to a 188 or 204 multiple */

	ctx->buf_siz = req->size;
	ctx->buf_cnt = req->count;
	ret = vb2_core_reqbufs(&ctx->vb_q, VB2_MEMORY_MMAP, &req->count);
	if (ret) {
		ctx->state = DVB_VB2_STATE_NONE;
		dprintk(1, "[%s] count=%d size=%d errno=%d\n", ctx->name,
			ctx->buf_cnt, ctx->buf_siz, ret);
		return ret;
	}
	ctx->state |= DVB_VB2_STATE_REQBUFS;
	dprintk(3, "[%s] count=%d size=%d\n", ctx->name,
		ctx->buf_cnt, ctx->buf_siz);

	return 0;
}
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
struct vb2_queue {int buf_struct_size; int min_buffers_needed; scalar_t__ num_buffers; int /*<<< orphan*/ * buf_ops; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct dvb_vb2_ctx* drv_priv; int /*<<< orphan*/  io_modes; scalar_t__ is_output; int /*<<< orphan*/  type; } ;
struct dvb_vb2_ctx {int nonblocking; int /*<<< orphan*/  name; int /*<<< orphan*/  state; int /*<<< orphan*/  dvb_q; int /*<<< orphan*/  slock; int /*<<< orphan*/  mutex; struct vb2_queue vb_q; } ;
struct dvb_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_BUF_TYPE_CAPTURE ; 
 int /*<<< orphan*/  DVB_VB2_NAME_MAX ; 
 int /*<<< orphan*/  DVB_VB2_STATE_INIT ; 
 int /*<<< orphan*/  DVB_VB2_STATE_NONE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VB2_MMAP ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dvb_vb2_buf_ops ; 
 int /*<<< orphan*/  dvb_vb2_qops ; 
 int /*<<< orphan*/  memset (struct dvb_vb2_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int vb2_core_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 

int dvb_vb2_init(struct dvb_vb2_ctx *ctx, const char *name, int nonblocking)
{
	struct vb2_queue *q = &ctx->vb_q;
	int ret;

	memset(ctx, 0, sizeof(struct dvb_vb2_ctx));
	q->type = DVB_BUF_TYPE_CAPTURE;
	/**capture type*/
	q->is_output = 0;
	/**only mmap is supported currently*/
	q->io_modes = VB2_MMAP;
	q->drv_priv = ctx;
	q->buf_struct_size = sizeof(struct dvb_buffer);
	q->min_buffers_needed = 1;
	q->ops = &dvb_vb2_qops;
	q->mem_ops = &vb2_vmalloc_memops;
	q->buf_ops = &dvb_vb2_buf_ops;
	q->num_buffers = 0;
	ret = vb2_core_queue_init(q);
	if (ret) {
		ctx->state = DVB_VB2_STATE_NONE;
		dprintk(1, "[%s] errno=%d\n", ctx->name, ret);
		return ret;
	}

	mutex_init(&ctx->mutex);
	spin_lock_init(&ctx->slock);
	INIT_LIST_HEAD(&ctx->dvb_q);

	strscpy(ctx->name, name, DVB_VB2_NAME_MAX);
	ctx->nonblocking = nonblocking;
	ctx->state = DVB_VB2_STATE_INIT;

	dprintk(3, "[%s]\n", ctx->name);

	return 0;
}
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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct dvb_vb2_ctx {int /*<<< orphan*/  name; struct vb2_queue vb_q; } ;
struct dmx_exportbuffer {int fd; int /*<<< orphan*/  index; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vb2_core_expbuf (struct vb2_queue*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dvb_vb2_expbuf(struct dvb_vb2_ctx *ctx, struct dmx_exportbuffer *exp)
{
	struct vb2_queue *q = &ctx->vb_q;
	int ret;

	ret = vb2_core_expbuf(&ctx->vb_q, &exp->fd, q->type, exp->index,
			      0, exp->flags);
	if (ret) {
		dprintk(1, "[%s] index=%d errno=%d\n", ctx->name,
			exp->index, ret);
		return ret;
	}
	dprintk(3, "[%s] index=%d fd=%d\n", ctx->name, exp->index, exp->fd);

	return 0;
}
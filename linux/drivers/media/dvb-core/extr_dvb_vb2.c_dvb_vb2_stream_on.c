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
struct dvb_vb2_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  state; struct vb2_queue vb_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_VB2_STATE_NONE ; 
 int /*<<< orphan*/  DVB_VB2_STATE_STREAMON ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,...) ; 
 int vb2_core_streamon (struct vb2_queue*,int /*<<< orphan*/ ) ; 

int dvb_vb2_stream_on(struct dvb_vb2_ctx *ctx)
{
	struct vb2_queue *q = &ctx->vb_q;
	int ret;

	ret = vb2_core_streamon(q, q->type);
	if (ret) {
		ctx->state = DVB_VB2_STATE_NONE;
		dprintk(1, "[%s] errno=%d\n", ctx->name, ret);
		return ret;
	}
	ctx->state |= DVB_VB2_STATE_STREAMON;
	dprintk(3, "[%s]\n", ctx->name);

	return 0;
}
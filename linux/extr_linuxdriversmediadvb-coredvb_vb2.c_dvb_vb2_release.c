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
struct vb2_queue {int dummy; } ;
struct dvb_vb2_ctx {int state; int /*<<< orphan*/  name; int /*<<< orphan*/  vb_q; } ;

/* Variables and functions */
 int DVB_VB2_STATE_INIT ; 
 int DVB_VB2_STATE_NONE ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_core_queue_release (struct vb2_queue*) ; 

int dvb_vb2_release(struct dvb_vb2_ctx *ctx)
{
	struct vb2_queue *q = (struct vb2_queue *)&ctx->vb_q;

	if (ctx->state & DVB_VB2_STATE_INIT)
		vb2_core_queue_release(q);

	ctx->state = DVB_VB2_STATE_NONE;
	dprintk(3, "[%s]\n", ctx->name);

	return 0;
}
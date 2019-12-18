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
struct dvb_vb2_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  vb_q; } ;
struct dmx_buffer {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_core_querybuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dmx_buffer*) ; 

int dvb_vb2_querybuf(struct dvb_vb2_ctx *ctx, struct dmx_buffer *b)
{
	vb2_core_querybuf(&ctx->vb_q, b->index, b);
	dprintk(3, "[%s] index=%d\n", ctx->name, b->index);
	return 0;
}
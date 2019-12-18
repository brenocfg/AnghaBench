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
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int vb2_core_qbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dmx_buffer*,int /*<<< orphan*/ *) ; 

int dvb_vb2_qbuf(struct dvb_vb2_ctx *ctx, struct dmx_buffer *b)
{
	int ret;

	ret = vb2_core_qbuf(&ctx->vb_q, b->index, b, NULL);
	if (ret) {
		dprintk(1, "[%s] index=%d errno=%d\n", ctx->name,
			b->index, ret);
		return ret;
	}
	dprintk(5, "[%s] index=%d\n", ctx->name, b->index);

	return 0;
}
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
struct dvb_vb2_ctx {unsigned int buf_cnt; unsigned int buf_siz; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct dvb_vb2_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int _queue_setup(struct vb2_queue *vq,
			unsigned int *nbuffers, unsigned int *nplanes,
			unsigned int sizes[], struct device *alloc_devs[])
{
	struct dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);

	ctx->buf_cnt = *nbuffers;
	*nplanes = 1;
	sizes[0] = ctx->buf_siz;

	/*
	 * videobuf2-vmalloc allocator is context-less so no need to set
	 * alloc_ctxs array.
	 */

	dprintk(3, "[%s] count=%d, size=%d\n", ctx->name,
		*nbuffers, sizes[0]);

	return 0;
}
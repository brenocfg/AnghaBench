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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct dvb_vb2_ctx {unsigned long buf_siz; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,...) ; 
 struct dvb_vb2_ctx* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 unsigned long vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int _buffer_prepare(struct vb2_buffer *vb)
{
	struct dvb_vb2_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	unsigned long size = ctx->buf_siz;

	if (vb2_plane_size(vb, 0) < size) {
		dprintk(1, "[%s] data will not fit into plane (%lu < %lu)\n",
			ctx->name, vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}

	vb2_set_plane_payload(vb, 0, size);
	dprintk(3, "[%s]\n", ctx->name);

	return 0;
}
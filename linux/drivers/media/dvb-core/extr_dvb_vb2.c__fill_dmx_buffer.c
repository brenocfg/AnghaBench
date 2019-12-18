#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vb2_buffer {TYPE_2__* planes; int /*<<< orphan*/  index; int /*<<< orphan*/  vb2_queue; } ;
struct dvb_vb2_ctx {int /*<<< orphan*/  name; } ;
struct dmx_buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  length; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {TYPE_1__ m; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 struct dvb_vb2_ctx* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _fill_dmx_buffer(struct vb2_buffer *vb, void *pb)
{
	struct dvb_vb2_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct dmx_buffer *b = pb;

	b->index = vb->index;
	b->length = vb->planes[0].length;
	b->bytesused = vb->planes[0].bytesused;
	b->offset = vb->planes[0].m.offset;
	dprintk(3, "[%s]\n", ctx->name);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vb2_buffer {TYPE_1__* vb2_queue; } ;
struct rga_frame {int /*<<< orphan*/  size; } ;
struct rga_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rga_frame*) ; 
 int PTR_ERR (struct rga_frame*) ; 
 struct rga_frame* rga_get_frame (struct rga_ctx*,int /*<<< orphan*/ ) ; 
 struct rga_ctx* vb2_get_drv_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rga_buf_prepare(struct vb2_buffer *vb)
{
	struct rga_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct rga_frame *f = rga_get_frame(ctx, vb->vb2_queue->type);

	if (IS_ERR(f))
		return PTR_ERR(f);

	vb2_set_plane_payload(vb, 0, f->size);

	return 0;
}
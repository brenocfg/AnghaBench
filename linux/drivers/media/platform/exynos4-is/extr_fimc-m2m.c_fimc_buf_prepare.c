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
struct vb2_buffer {TYPE_2__* vb2_queue; } ;
struct fimc_frame {int /*<<< orphan*/ * payload; TYPE_1__* fmt; } ;
struct fimc_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int memplanes; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fimc_frame*) ; 
 int PTR_ERR (struct fimc_frame*) ; 
 struct fimc_frame* ctx_get_frame (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 struct fimc_ctx* vb2_get_drv_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_buf_prepare(struct vb2_buffer *vb)
{
	struct fimc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct fimc_frame *frame;
	int i;

	frame = ctx_get_frame(ctx, vb->vb2_queue->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	for (i = 0; i < frame->fmt->memplanes; i++)
		vb2_set_plane_payload(vb, i, frame->payload[i]);

	return 0;
}
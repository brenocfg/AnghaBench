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
struct mtk_mdp_frame {int /*<<< orphan*/ * payload; TYPE_1__* fmt; } ;
struct mtk_mdp_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 struct mtk_mdp_frame* mtk_mdp_ctx_get_frame (struct mtk_mdp_ctx*,int /*<<< orphan*/ ) ; 
 struct mtk_mdp_ctx* vb2_get_drv_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_m2m_buf_prepare(struct vb2_buffer *vb)
{
	struct mtk_mdp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct mtk_mdp_frame *frame;
	int i;

	frame = mtk_mdp_ctx_get_frame(ctx, vb->vb2_queue->type);

	if (!V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		for (i = 0; i < frame->fmt->num_planes; i++)
			vb2_set_plane_payload(vb, i, frame->payload[i]);
	}

	return 0;
}
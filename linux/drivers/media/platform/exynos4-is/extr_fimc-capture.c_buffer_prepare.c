#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {struct fimc_ctx* drv_priv; } ;
struct vb2_buffer {struct vb2_queue* vb2_queue; } ;
struct TYPE_9__ {unsigned long* payload; TYPE_5__* fmt; } ;
struct fimc_ctx {TYPE_3__* fimc_dev; TYPE_4__ d_frame; } ;
struct TYPE_10__ {int memplanes; } ;
struct TYPE_6__ {int /*<<< orphan*/  vdev; } ;
struct TYPE_7__ {TYPE_1__ ve; } ;
struct TYPE_8__ {TYPE_2__ vid_cap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 
 unsigned long vb2_plane_size (struct vb2_buffer*,int) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int,unsigned long) ; 

__attribute__((used)) static int buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct fimc_ctx *ctx = vq->drv_priv;
	int i;

	if (ctx->d_frame.fmt == NULL)
		return -EINVAL;

	for (i = 0; i < ctx->d_frame.fmt->memplanes; i++) {
		unsigned long size = ctx->d_frame.payload[i];

		if (vb2_plane_size(vb, i) < size) {
			v4l2_err(&ctx->fimc_dev->vid_cap.ve.vdev,
				 "User buffer too small (%ld < %ld)\n",
				 vb2_plane_size(vb, i), size);
			return -EINVAL;
		}
		vb2_set_plane_payload(vb, i, size);
	}

	return 0;
}
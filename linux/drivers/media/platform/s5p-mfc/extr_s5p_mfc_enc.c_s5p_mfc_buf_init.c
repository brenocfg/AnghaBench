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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {scalar_t__ type; int /*<<< orphan*/  drv_priv; } ;
struct vb2_buffer {unsigned int index; struct vb2_queue* vb2_queue; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/  src_bufs_cnt; TYPE_5__* src_bufs; int /*<<< orphan*/  src_fmt; int /*<<< orphan*/  dst_bufs_cnt; TYPE_2__* dst_bufs; int /*<<< orphan*/  dst_fmt; } ;
struct TYPE_8__ {void* chroma; void* luma; } ;
struct TYPE_9__ {TYPE_3__ raw; } ;
struct TYPE_10__ {TYPE_4__ cookie; struct vb2_v4l2_buffer* b; } ;
struct TYPE_6__ {void* stream; } ;
struct TYPE_7__ {TYPE_1__ cookie; struct vb2_v4l2_buffer* b; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int check_vb_with_fmt (int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*,scalar_t__) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 void* vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 

__attribute__((used)) static int s5p_mfc_buf_init(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	unsigned int i;
	int ret;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		ret = check_vb_with_fmt(ctx->dst_fmt, vb);
		if (ret < 0)
			return ret;
		i = vb->index;
		ctx->dst_bufs[i].b = vbuf;
		ctx->dst_bufs[i].cookie.stream =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->dst_bufs_cnt++;
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = check_vb_with_fmt(ctx->src_fmt, vb);
		if (ret < 0)
			return ret;
		i = vb->index;
		ctx->src_bufs[i].b = vbuf;
		ctx->src_bufs[i].cookie.raw.luma =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->src_bufs[i].cookie.raw.chroma =
					vb2_dma_contig_plane_dma_addr(vb, 1);
		ctx->src_bufs_cnt++;
	} else {
		mfc_err("invalid queue type: %d\n", vq->type);
		return -EINVAL;
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {scalar_t__ type; int /*<<< orphan*/  drv_priv; } ;
struct vb2_buffer {unsigned int index; struct vb2_queue* vb2_queue; } ;
struct s5p_mfc_ctx {scalar_t__ capture_state; scalar_t__ luma_size; scalar_t__ chroma_size; scalar_t__ dec_src_buf_size; int /*<<< orphan*/  src_bufs_cnt; TYPE_6__* src_bufs; int /*<<< orphan*/  dst_bufs_cnt; TYPE_4__* dst_bufs; TYPE_1__* dst_fmt; } ;
struct TYPE_11__ {void* stream; } ;
struct TYPE_12__ {TYPE_5__ cookie; struct vb2_v4l2_buffer* b; } ;
struct TYPE_8__ {void* chroma; void* luma; } ;
struct TYPE_9__ {TYPE_2__ raw; } ;
struct TYPE_10__ {TYPE_3__ cookie; struct vb2_v4l2_buffer* b; } ;
struct TYPE_7__ {unsigned int num_planes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (void*) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ QUEUE_BUFS_MMAPED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 void* vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int) ; 

__attribute__((used)) static int s5p_mfc_buf_init(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	unsigned int i;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (ctx->capture_state == QUEUE_BUFS_MMAPED)
			return 0;
		for (i = 0; i < ctx->dst_fmt->num_planes; i++) {
			if (IS_ERR_OR_NULL(ERR_PTR(
					vb2_dma_contig_plane_dma_addr(vb, i)))) {
				mfc_err("Plane mem not allocated\n");
				return -EINVAL;
			}
		}
		if (vb2_plane_size(vb, 0) < ctx->luma_size ||
			vb2_plane_size(vb, 1) < ctx->chroma_size) {
			mfc_err("Plane buffer (CAPTURE) is too small\n");
			return -EINVAL;
		}
		i = vb->index;
		ctx->dst_bufs[i].b = vbuf;
		ctx->dst_bufs[i].cookie.raw.luma =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->dst_bufs[i].cookie.raw.chroma =
					vb2_dma_contig_plane_dma_addr(vb, 1);
		ctx->dst_bufs_cnt++;
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (IS_ERR_OR_NULL(ERR_PTR(
					vb2_dma_contig_plane_dma_addr(vb, 0)))) {
			mfc_err("Plane memory not allocated\n");
			return -EINVAL;
		}
		if (vb2_plane_size(vb, 0) < ctx->dec_src_buf_size) {
			mfc_err("Plane buffer (OUTPUT) is too small\n");
			return -EINVAL;
		}

		i = vb->index;
		ctx->src_bufs[i].b = vbuf;
		ctx->src_bufs[i].cookie.stream =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->src_bufs_cnt++;
	} else {
		mfc_err("s5p_mfc_buf_init: unknown queue type\n");
		return -EINVAL;
	}
	return 0;
}
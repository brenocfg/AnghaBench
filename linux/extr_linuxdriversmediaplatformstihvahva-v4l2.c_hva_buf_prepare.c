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
struct vb2_v4l2_buffer {scalar_t__ field; int /*<<< orphan*/  vb2_buf; } ;
struct vb2_buffer {int /*<<< orphan*/  index; TYPE_1__* vb2_queue; } ;
struct hva_stream {int prepared; void* paddr; void* vaddr; int /*<<< orphan*/  size; } ;
struct hva_frame {int prepared; void* paddr; void* vaddr; int /*<<< orphan*/  info; } ;
struct hva_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  frameinfo; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 struct hva_frame* to_hva_frame (struct vb2_v4l2_buffer*) ; 
 struct hva_stream* to_hva_stream (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 void* vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hva_ctx* vb2_get_drv_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  vb2_plane_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_buf_prepare(struct vb2_buffer *vb)
{
	struct hva_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct device *dev = ctx_to_dev(ctx);
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	if (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		struct hva_frame *frame = to_hva_frame(vbuf);

		if (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		if (vbuf->field != V4L2_FIELD_NONE) {
			dev_dbg(dev,
				"%s frame[%d] prepare: %d field not supported\n",
				ctx->name, vb->index, vbuf->field);
			return -EINVAL;
		}

		if (!frame->prepared) {
			/* get memory addresses */
			frame->vaddr = vb2_plane_vaddr(&vbuf->vb2_buf, 0);
			frame->paddr = vb2_dma_contig_plane_dma_addr(
					&vbuf->vb2_buf, 0);
			frame->info = ctx->frameinfo;
			frame->prepared = true;

			dev_dbg(dev,
				"%s frame[%d] prepared; virt=%p, phy=%pad\n",
				ctx->name, vb->index,
				frame->vaddr, &frame->paddr);
		}
	} else {
		struct hva_stream *stream = to_hva_stream(vbuf);

		if (!stream->prepared) {
			/* get memory addresses */
			stream->vaddr = vb2_plane_vaddr(&vbuf->vb2_buf, 0);
			stream->paddr = vb2_dma_contig_plane_dma_addr(
					&vbuf->vb2_buf, 0);
			stream->size = vb2_plane_size(&vbuf->vb2_buf, 0);
			stream->prepared = true;

			dev_dbg(dev,
				"%s stream[%d] prepared; virt=%p, phy=%pad\n",
				ctx->name, vb->index,
				stream->vaddr, &stream->paddr);
		}
	}

	return 0;
}
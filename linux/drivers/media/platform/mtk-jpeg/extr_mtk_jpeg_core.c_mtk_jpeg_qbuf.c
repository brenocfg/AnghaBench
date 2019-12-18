#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {scalar_t__ num_buffers; } ;
struct vb2_buffer {int dummy; } ;
struct v4l2_fh {int /*<<< orphan*/  m2m_ctx; } ;
struct TYPE_6__ {TYPE_2__* planes; } ;
struct v4l2_buffer {scalar_t__ index; TYPE_3__ m; int /*<<< orphan*/  type; } ;
struct mtk_jpeg_src_buf {int /*<<< orphan*/  flags; } ;
struct mtk_jpeg_ctx {TYPE_1__* jpeg; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_5__ {scalar_t__ bytesused; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_JPEG_BUF_FLAGS_INIT ; 
 int /*<<< orphan*/  MTK_JPEG_BUF_FLAGS_LAST_FRAME ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mtk_jpeg_ctx* mtk_jpeg_fh_to_ctx (void*) ; 
 struct mtk_jpeg_src_buf* mtk_jpeg_vb2_to_srcbuf (struct vb2_buffer*) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_m2m_qbuf (struct file*,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 struct vb2_buffer* vb2_get_buffer (struct vb2_queue*,scalar_t__) ; 

__attribute__((used)) static int mtk_jpeg_qbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
	struct v4l2_fh *fh = file->private_data;
	struct mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	struct vb2_queue *vq;
	struct vb2_buffer *vb;
	struct mtk_jpeg_src_buf *jpeg_src_buf;

	if (buf->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		goto end;

	vq = v4l2_m2m_get_vq(fh->m2m_ctx, buf->type);
	if (buf->index >= vq->num_buffers) {
		dev_err(ctx->jpeg->dev, "buffer index out of range\n");
		return -EINVAL;
	}

	vb = vb2_get_buffer(vq, buf->index);
	jpeg_src_buf = mtk_jpeg_vb2_to_srcbuf(vb);
	jpeg_src_buf->flags = (buf->m.planes[0].bytesused == 0) ?
		MTK_JPEG_BUF_FLAGS_LAST_FRAME : MTK_JPEG_BUF_FLAGS_INIT;
end:
	return v4l2_m2m_qbuf(file, fh->m2m_ctx, buf);
}
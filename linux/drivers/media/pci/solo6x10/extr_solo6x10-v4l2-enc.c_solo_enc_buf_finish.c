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
struct vb2_v4l2_buffer {int flags; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct solo_enc_dev {int fmt; int /*<<< orphan*/  jpeg_len; int /*<<< orphan*/  jpeg_header; int /*<<< orphan*/  vop_len; int /*<<< orphan*/  vop; } ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int V4L2_BUF_FLAG_KEYFRAME ; 
#define  V4L2_PIX_FMT_H264 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct sg_table* vb2_dma_sg_plane_desc (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct solo_enc_dev* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_enc_buf_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct solo_enc_dev *solo_enc = vb2_get_drv_priv(vb->vb2_queue);
	struct sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);

	switch (solo_enc->fmt) {
	case V4L2_PIX_FMT_MPEG4:
	case V4L2_PIX_FMT_H264:
		if (vbuf->flags & V4L2_BUF_FLAG_KEYFRAME)
			sg_copy_from_buffer(sgt->sgl, sgt->nents,
					solo_enc->vop, solo_enc->vop_len);
		break;
	default: /* V4L2_PIX_FMT_MJPEG */
		sg_copy_from_buffer(sgt->sgl, sgt->nents,
				solo_enc->jpeg_header, solo_enc->jpeg_len);
		break;
	}
}
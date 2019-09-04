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
typedef  int /*<<< orphan*/  vop_header ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  flags; } ;
struct vb2_buffer {int dummy; } ;
struct solo_enc_dev {scalar_t__ jpeg_len; struct solo_dev* solo_dev; } ;
struct solo_dev {int dummy; } ;
struct sg_table {int dummy; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_ALIGN ; 
 int EIO ; 
 scalar_t__ SOLO_JPEG_EXT_ADDR (struct solo_dev*) ; 
 int /*<<< orphan*/  SOLO_JPEG_EXT_SIZE (struct solo_dev*) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_KEYFRAME ; 
 int solo_send_desc (struct solo_enc_dev*,scalar_t__,struct sg_table*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct sg_table* vb2_dma_sg_plane_desc (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vop_jpeg_offset (int /*<<< orphan*/  const*) ; 
 scalar_t__ vop_jpeg_size (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int solo_fill_jpeg(struct solo_enc_dev *solo_enc,
			  struct vb2_buffer *vb, const vop_header *vh)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	struct sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	int frame_size;

	vbuf->flags |= V4L2_BUF_FLAG_KEYFRAME;

	if (vb2_plane_size(vb, 0) < vop_jpeg_size(vh) + solo_enc->jpeg_len)
		return -EIO;

	frame_size = ALIGN(vop_jpeg_size(vh) + solo_enc->jpeg_len, DMA_ALIGN);
	vb2_set_plane_payload(vb, 0, vop_jpeg_size(vh) + solo_enc->jpeg_len);

	return solo_send_desc(solo_enc, solo_enc->jpeg_len, sgt,
			     vop_jpeg_offset(vh) - SOLO_JPEG_EXT_ADDR(solo_dev),
			     frame_size, SOLO_JPEG_EXT_ADDR(solo_dev),
			     SOLO_JPEG_EXT_SIZE(solo_dev));
}
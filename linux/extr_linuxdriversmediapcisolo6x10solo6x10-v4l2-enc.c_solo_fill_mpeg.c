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
struct vb2_v4l2_buffer {int flags; } ;
struct vb2_buffer {int dummy; } ;
struct solo_enc_dev {int vop_len; struct solo_dev* solo_dev; } ;
struct solo_dev {int dummy; } ;
struct sg_table {int dummy; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_ALIGN ; 
 int EIO ; 
 int SOLO_MP4E_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_MP4E_EXT_SIZE (struct solo_dev*) ; 
 int V4L2_BUF_FLAG_BFRAME ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_PFRAME ; 
 int solo_send_desc (struct solo_enc_dev*,int,struct sg_table*,int,int,int,int) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct sg_table* vb2_dma_sg_plane_desc (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,scalar_t__) ; 
 int vop_mpeg_offset (int /*<<< orphan*/  const*) ; 
 scalar_t__ vop_mpeg_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vop_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int solo_fill_mpeg(struct solo_enc_dev *solo_enc,
		struct vb2_buffer *vb, const vop_header *vh)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	struct sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	int frame_off, frame_size;
	int skip = 0;

	if (vb2_plane_size(vb, 0) < vop_mpeg_size(vh))
		return -EIO;

	/* If this is a key frame, add extra header */
	vbuf->flags &= ~(V4L2_BUF_FLAG_KEYFRAME | V4L2_BUF_FLAG_PFRAME |
		V4L2_BUF_FLAG_BFRAME);
	if (!vop_type(vh)) {
		skip = solo_enc->vop_len;
		vbuf->flags |= V4L2_BUF_FLAG_KEYFRAME;
		vb2_set_plane_payload(vb, 0, vop_mpeg_size(vh) +
			solo_enc->vop_len);
	} else {
		vbuf->flags |= V4L2_BUF_FLAG_PFRAME;
		vb2_set_plane_payload(vb, 0, vop_mpeg_size(vh));
	}

	/* Now get the actual mpeg payload */
	frame_off = (vop_mpeg_offset(vh) - SOLO_MP4E_EXT_ADDR(solo_dev) +
		sizeof(*vh)) % SOLO_MP4E_EXT_SIZE(solo_dev);
	frame_size = ALIGN(vop_mpeg_size(vh) + skip, DMA_ALIGN);

	return solo_send_desc(solo_enc, skip, sgt, frame_off, frame_size,
			SOLO_MP4E_EXT_ADDR(solo_dev),
			SOLO_MP4E_EXT_SIZE(solo_dev));
}
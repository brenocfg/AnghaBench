#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_file {int dummy; } ;
struct drm_device_dma {struct drm_buf** buflist; } ;
struct drm_device {TYPE_1__* agp_buffer_map; struct drm_device_dma* dma; int /*<<< orphan*/ * dev_private; } ;
struct drm_buf {int offset; int used; scalar_t__ pending; struct drm_file* file_priv; TYPE_2__* dev_private; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;
struct TYPE_6__ {int discard; } ;
typedef  TYPE_2__ drm_r128_buf_priv_t ;
struct TYPE_7__ {int format; size_t idx; int width; int height; int pitch; int offset; int y; int x; } ;
typedef  TYPE_3__ drm_r128_blit_t ;
struct TYPE_5__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R128_CNTL_HOSTDATA_BLT ; 
#define  R128_DATATYPE_ARGB1555 135 
#define  R128_DATATYPE_ARGB4444 134 
#define  R128_DATATYPE_ARGB8888 133 
#define  R128_DATATYPE_CI8 132 
#define  R128_DATATYPE_RGB565 131 
#define  R128_DATATYPE_RGB8 130 
#define  R128_DATATYPE_VYUY422 129 
#define  R128_DATATYPE_YVYU422 128 
 int R128_DP_SRC_SOURCE_HOST_DATA ; 
 int R128_GMC_AUX_CLIP_DIS ; 
 int R128_GMC_BRUSH_NONE ; 
 int R128_GMC_CLR_CMP_CNTL_DIS ; 
 int R128_GMC_DST_PITCH_OFFSET_CNTL ; 
 int R128_GMC_SRC_DATATYPE_COLOR ; 
 int R128_GMC_WR_MSK_DIS ; 
 int R128_PC_FLUSH_GUI ; 
 int /*<<< orphan*/  R128_PC_GUI_CTLSTAT ; 
 int R128_PC_RI_GUI ; 
 int R128_ROP3_S ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  r128_cce_dispatch_indirect (struct drm_device*,struct drm_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r128_cce_dispatch_blit(struct drm_device *dev,
				  struct drm_file *file_priv,
				  drm_r128_blit_t *blit)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf *buf;
	drm_r128_buf_priv_t *buf_priv;
	u32 *data;
	int dword_shift, dwords;
	RING_LOCALS;
	DRM_DEBUG("\n");

	/* The compiler won't optimize away a division by a variable,
	 * even if the only legal values are powers of two.  Thus, we'll
	 * use a shift instead.
	 */
	switch (blit->format) {
	case R128_DATATYPE_ARGB8888:
		dword_shift = 0;
		break;
	case R128_DATATYPE_ARGB1555:
	case R128_DATATYPE_RGB565:
	case R128_DATATYPE_ARGB4444:
	case R128_DATATYPE_YVYU422:
	case R128_DATATYPE_VYUY422:
		dword_shift = 1;
		break;
	case R128_DATATYPE_CI8:
	case R128_DATATYPE_RGB8:
		dword_shift = 2;
		break;
	default:
		DRM_ERROR("invalid blit format %d\n", blit->format);
		return -EINVAL;
	}

	/* Flush the pixel cache, and mark the contents as Read Invalid.
	 * This ensures no pixel data gets mixed up with the texture
	 * data from the host data blit, otherwise part of the texture
	 * image may be corrupted.
	 */
	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_PC_GUI_CTLSTAT, 0));
	OUT_RING(R128_PC_RI_GUI | R128_PC_FLUSH_GUI);

	ADVANCE_RING();

	/* Dispatch the indirect buffer.
	 */
	buf = dma->buflist[blit->idx];
	buf_priv = buf->dev_private;

	if (buf->file_priv != file_priv) {
		DRM_ERROR("process %d using buffer owned by %p\n",
			  task_pid_nr(current), buf->file_priv);
		return -EINVAL;
	}
	if (buf->pending) {
		DRM_ERROR("sending pending buffer %d\n", blit->idx);
		return -EINVAL;
	}

	buf_priv->discard = 1;

	dwords = (blit->width * blit->height) >> dword_shift;

	data = (u32 *) ((char *)dev->agp_buffer_map->handle + buf->offset);

	data[0] = cpu_to_le32(CCE_PACKET3(R128_CNTL_HOSTDATA_BLT, dwords + 6));
	data[1] = cpu_to_le32((R128_GMC_DST_PITCH_OFFSET_CNTL |
			       R128_GMC_BRUSH_NONE |
			       (blit->format << 8) |
			       R128_GMC_SRC_DATATYPE_COLOR |
			       R128_ROP3_S |
			       R128_DP_SRC_SOURCE_HOST_DATA |
			       R128_GMC_CLR_CMP_CNTL_DIS |
			       R128_GMC_AUX_CLIP_DIS | R128_GMC_WR_MSK_DIS));

	data[2] = cpu_to_le32((blit->pitch << 21) | (blit->offset >> 5));
	data[3] = cpu_to_le32(0xffffffff);
	data[4] = cpu_to_le32(0xffffffff);
	data[5] = cpu_to_le32((blit->y << 16) | blit->x);
	data[6] = cpu_to_le32((blit->height << 16) | blit->width);
	data[7] = cpu_to_le32(dwords);

	buf->used = (dwords + 8) * sizeof(u32);

	r128_cce_dispatch_indirect(dev, buf, 0, buf->used);

	/* Flush the pixel cache after the blit completes.  This ensures
	 * the texture data is written out to memory before rendering
	 * continues.
	 */
	BEGIN_RING(2);

	OUT_RING(CCE_PACKET0(R128_PC_GUI_CTLSTAT, 0));
	OUT_RING(R128_PC_FLUSH_GUI);

	ADVANCE_RING();

	return 0;
}
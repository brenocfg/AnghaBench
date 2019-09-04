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
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_clip_rect {int x1; int y1; int x2; int y2; } ;
struct TYPE_5__ {int nbox; struct drm_clip_rect* boxes; } ;
typedef  TYPE_1__ drm_r128_sarea_t ;
struct TYPE_6__ {int current_page; int color_fmt; int front_pitch_offset_c; int back_pitch_offset_c; int depth_fmt; int depth_pitch_offset_c; scalar_t__ page_flipping; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_r128_private_t ;
struct TYPE_7__ {unsigned int flags; int color_mask; int clear_color; int clear_depth; } ;
typedef  TYPE_3__ drm_r128_clear_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 unsigned int R128_BACK ; 
 int /*<<< orphan*/  R128_CNTL_PAINT_MULTI ; 
 unsigned int R128_DEPTH ; 
 int /*<<< orphan*/  R128_DP_WRITE_MASK ; 
 unsigned int R128_FRONT ; 
 int R128_GMC_AUX_CLIP_DIS ; 
 int R128_GMC_BRUSH_SOLID_COLOR ; 
 int R128_GMC_CLR_CMP_CNTL_DIS ; 
 int R128_GMC_DST_PITCH_OFFSET_CNTL ; 
 int R128_GMC_SRC_DATATYPE_COLOR ; 
 int R128_GMC_WR_MSK_DIS ; 
 int R128_ROP3_P ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void r128_cce_dispatch_clear(struct drm_device *dev,
				    drm_r128_clear_t *clear)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	int nbox = sarea_priv->nbox;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	unsigned int flags = clear->flags;
	int i;
	RING_LOCALS;
	DRM_DEBUG("\n");

	if (dev_priv->page_flipping && dev_priv->current_page == 1) {
		unsigned int tmp = flags;

		flags &= ~(R128_FRONT | R128_BACK);
		if (tmp & R128_FRONT)
			flags |= R128_BACK;
		if (tmp & R128_BACK)
			flags |= R128_FRONT;
	}

	for (i = 0; i < nbox; i++) {
		int x = pbox[i].x1;
		int y = pbox[i].y1;
		int w = pbox[i].x2 - x;
		int h = pbox[i].y2 - y;

		DRM_DEBUG("dispatch clear %d,%d-%d,%d flags 0x%x\n",
			  pbox[i].x1, pbox[i].y1, pbox[i].x2,
			  pbox[i].y2, flags);

		if (flags & (R128_FRONT | R128_BACK)) {
			BEGIN_RING(2);

			OUT_RING(CCE_PACKET0(R128_DP_WRITE_MASK, 0));
			OUT_RING(clear->color_mask);

			ADVANCE_RING();
		}

		if (flags & R128_FRONT) {
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->color_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_AUX_CLIP_DIS);

			OUT_RING(dev_priv->front_pitch_offset_c);
			OUT_RING(clear->clear_color);

			OUT_RING((x << 16) | y);
			OUT_RING((w << 16) | h);

			ADVANCE_RING();
		}

		if (flags & R128_BACK) {
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->color_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_AUX_CLIP_DIS);

			OUT_RING(dev_priv->back_pitch_offset_c);
			OUT_RING(clear->clear_color);

			OUT_RING((x << 16) | y);
			OUT_RING((w << 16) | h);

			ADVANCE_RING();
		}

		if (flags & R128_DEPTH) {
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->depth_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_AUX_CLIP_DIS | R128_GMC_WR_MSK_DIS);

			OUT_RING(dev_priv->depth_pitch_offset_c);
			OUT_RING(clear->clear_depth);

			OUT_RING((x << 16) | y);
			OUT_RING((w << 16) | h);

			ADVANCE_RING();
		}
	}
}
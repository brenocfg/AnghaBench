#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {TYPE_1__* agp_buffer_map; TYPE_3__* dev_private; } ;
struct drm_buf {int offset; int pending; TYPE_4__* dev_private; } ;
struct TYPE_8__ {int vc_format; int dirty; int nbox; int /*<<< orphan*/  last_dispatch; int /*<<< orphan*/ * boxes; } ;
typedef  TYPE_2__ drm_r128_sarea_t ;
struct TYPE_9__ {int cce_buffers_offset; TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_r128_private_t ;
struct TYPE_10__ {int prim; int dispatched; int /*<<< orphan*/  age; scalar_t__ discard; } ;
typedef  TYPE_4__ drm_r128_buf_priv_t ;
struct TYPE_7__ {int offset; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CCE_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,int) ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R128_3D_RNDR_GEN_INDX_PRIM ; 
 int R128_CCE_VC_CNTL_PRIM_WALK_IND ; 
 int /*<<< orphan*/  R128_LAST_DISPATCH_REG ; 
 int R128_MAX_VB_VERTS ; 
 int R128_UPLOAD_CLIPRECTS ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  r128_cce_dispatch_indirect (struct drm_device*,struct drm_buf*,int,int) ; 
 int /*<<< orphan*/  r128_emit_clip_rects (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r128_emit_state (TYPE_3__*) ; 
 int /*<<< orphan*/  r128_print_dirty (char*,int) ; 

__attribute__((used)) static void r128_cce_dispatch_indices(struct drm_device *dev,
				      struct drm_buf *buf,
				      int start, int end, int count)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_buf_priv_t *buf_priv = buf->dev_private;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	int format = sarea_priv->vc_format;
	int offset = dev->agp_buffer_map->offset - dev_priv->cce_buffers_offset;
	int prim = buf_priv->prim;
	u32 *data;
	int dwords;
	int i = 0;
	RING_LOCALS;
	DRM_DEBUG("indices: s=%d e=%d c=%d\n", start, end, count);

	if (0)
		r128_print_dirty("dispatch_indices", sarea_priv->dirty);

	if (start != end) {
		buf_priv->dispatched = 1;

		if (sarea_priv->dirty & ~R128_UPLOAD_CLIPRECTS)
			r128_emit_state(dev_priv);

		dwords = (end - start + 3) / sizeof(u32);

		data = (u32 *) ((char *)dev->agp_buffer_map->handle
				+ buf->offset + start);

		data[0] = cpu_to_le32(CCE_PACKET3(R128_3D_RNDR_GEN_INDX_PRIM,
						  dwords - 2));

		data[1] = cpu_to_le32(offset);
		data[2] = cpu_to_le32(R128_MAX_VB_VERTS);
		data[3] = cpu_to_le32(format);
		data[4] = cpu_to_le32((prim | R128_CCE_VC_CNTL_PRIM_WALK_IND |
				       (count << 16)));

		if (count & 0x1) {
#ifdef __LITTLE_ENDIAN
			data[dwords - 1] &= 0x0000ffff;
#else
			data[dwords - 1] &= 0xffff0000;
#endif
		}

		do {
			/* Emit the next set of up to three cliprects */
			if (i < sarea_priv->nbox) {
				r128_emit_clip_rects(dev_priv,
						     &sarea_priv->boxes[i],
						     sarea_priv->nbox - i);
			}

			r128_cce_dispatch_indirect(dev, buf, start, end);

			i += 3;
		} while (i < sarea_priv->nbox);
	}

	if (buf_priv->discard) {
		buf_priv->age = dev_priv->sarea_priv->last_dispatch;

		/* Emit the vertex buffer age */
		BEGIN_RING(2);

		OUT_RING(CCE_PACKET0(R128_LAST_DISPATCH_REG, 0));
		OUT_RING(buf_priv->age);

		ADVANCE_RING();

		buf->pending = 1;
		/* FIXME: Check dispatched field */
		buf_priv->dispatched = 0;
	}

	dev_priv->sarea_priv->last_dispatch++;

	sarea_priv->dirty &= ~R128_UPLOAD_CLIPRECTS;
	sarea_priv->nbox = 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_buf {int bus_address; int used; int pending; int /*<<< orphan*/  idx; TYPE_3__* dev_private; } ;
struct TYPE_6__ {int vc_format; int nbox; int dirty; int last_dispatch; int /*<<< orphan*/ * boxes; } ;
typedef  TYPE_1__ drm_r128_sarea_t ;
struct TYPE_7__ {TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_r128_private_t ;
struct TYPE_8__ {int prim; int dispatched; int age; scalar_t__ discard; } ;
typedef  TYPE_3__ drm_r128_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R128_3D_RNDR_GEN_INDX_PRIM ; 
 int R128_CCE_VC_CNTL_NUM_SHIFT ; 
 int R128_CCE_VC_CNTL_PRIM_WALK_LIST ; 
 int /*<<< orphan*/  R128_LAST_DISPATCH_REG ; 
 int R128_UPLOAD_CLIPRECTS ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  r128_emit_clip_rects (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r128_emit_state (TYPE_2__*) ; 
 int /*<<< orphan*/  r128_print_dirty (char*,int) ; 

__attribute__((used)) static void r128_cce_dispatch_vertex(struct drm_device *dev, struct drm_buf *buf)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_buf_priv_t *buf_priv = buf->dev_private;
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;
	int format = sarea_priv->vc_format;
	int offset = buf->bus_address;
	int size = buf->used;
	int prim = buf_priv->prim;
	int i = 0;
	RING_LOCALS;
	DRM_DEBUG("buf=%d nbox=%d\n", buf->idx, sarea_priv->nbox);

	if (0)
		r128_print_dirty("dispatch_vertex", sarea_priv->dirty);

	if (buf->used) {
		buf_priv->dispatched = 1;

		if (sarea_priv->dirty & ~R128_UPLOAD_CLIPRECTS)
			r128_emit_state(dev_priv);

		do {
			/* Emit the next set of up to three cliprects */
			if (i < sarea_priv->nbox) {
				r128_emit_clip_rects(dev_priv,
						     &sarea_priv->boxes[i],
						     sarea_priv->nbox - i);
			}

			/* Emit the vertex buffer rendering commands */
			BEGIN_RING(5);

			OUT_RING(CCE_PACKET3(R128_3D_RNDR_GEN_INDX_PRIM, 3));
			OUT_RING(offset);
			OUT_RING(size);
			OUT_RING(format);
			OUT_RING(prim | R128_CCE_VC_CNTL_PRIM_WALK_LIST |
				 (size << R128_CCE_VC_CNTL_NUM_SHIFT));

			ADVANCE_RING();

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
		buf->used = 0;
		/* FIXME: Check dispatched field */
		buf_priv->dispatched = 0;
	}

	dev_priv->sarea_priv->last_dispatch++;

	sarea_priv->dirty &= ~R128_UPLOAD_CLIPRECTS;
	sarea_priv->nbox = 0;
}
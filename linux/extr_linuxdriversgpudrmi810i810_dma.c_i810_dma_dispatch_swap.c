#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_clip_rect {unsigned int x2; unsigned int x1; unsigned int y2; unsigned int y1; } ;
struct TYPE_3__ {int nbox; struct drm_clip_rect* boxes; } ;
typedef  TYPE_1__ drm_i810_sarea_t ;
struct TYPE_4__ {int pitch; int w; int h; scalar_t__ current_page; unsigned int front_offset; unsigned int back_offset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_i810_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 int /*<<< orphan*/  BEGIN_LP_RING (int) ; 
 int BR00_BITBLT_CLIENT ; 
 int BR00_OP_SRC_COPY_BLT ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int I810_NR_SAREA_CLIPRECTS ; 
 int /*<<< orphan*/  OUT_RING (unsigned int) ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  i810_kernel_lost_context (struct drm_device*) ; 

__attribute__((used)) static void i810_dma_dispatch_swap(struct drm_device *dev)
{
	drm_i810_private_t *dev_priv = dev->dev_private;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	int nbox = sarea_priv->nbox;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	int pitch = dev_priv->pitch;
	int cpp = 2;
	int i;
	RING_LOCALS;

	DRM_DEBUG("swapbuffers\n");

	i810_kernel_lost_context(dev);

	if (nbox > I810_NR_SAREA_CLIPRECTS)
		nbox = I810_NR_SAREA_CLIPRECTS;

	for (i = 0; i < nbox; i++, pbox++) {
		unsigned int w = pbox->x2 - pbox->x1;
		unsigned int h = pbox->y2 - pbox->y1;
		unsigned int dst = pbox->x1 * cpp + pbox->y1 * pitch;
		unsigned int start = dst;

		if (pbox->x1 > pbox->x2 ||
		    pbox->y1 > pbox->y2 ||
		    pbox->x2 > dev_priv->w || pbox->y2 > dev_priv->h)
			continue;

		BEGIN_LP_RING(6);
		OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_SRC_COPY_BLT | 0x4);
		OUT_RING(pitch | (0xCC << 16));
		OUT_RING((h << 16) | (w * cpp));
		if (dev_priv->current_page == 0)
			OUT_RING(dev_priv->front_offset + start);
		else
			OUT_RING(dev_priv->back_offset + start);
		OUT_RING(pitch);
		if (dev_priv->current_page == 0)
			OUT_RING(dev_priv->back_offset + start);
		else
			OUT_RING(dev_priv->front_offset + start);
		ADVANCE_LP_RING();
	}
}
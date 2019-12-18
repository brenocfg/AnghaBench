#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_buf {scalar_t__ used; scalar_t__ pending; int /*<<< orphan*/  idx; int /*<<< orphan*/  bus_address; TYPE_3__* dev_private; } ;
struct TYPE_7__ {int nbox; int /*<<< orphan*/ * boxes; int /*<<< orphan*/  dirty; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_8__ {unsigned int dma_access; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_9__ {int dispatched; scalar_t__ discard; } ;
typedef  TYPE_3__ drm_mga_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  AGE_BUFFER (TYPE_3__*) ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FLUSH_DMA () ; 
 int /*<<< orphan*/  MGA_DMAPAD ; 
 int /*<<< orphan*/  MGA_EMIT_STATE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGA_SETUPADDRESS ; 
 int /*<<< orphan*/  MGA_SETUPEND ; 
 int /*<<< orphan*/  mga_emit_clip_rect (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mga_freelist_put (struct drm_device*,struct drm_buf*) ; 

__attribute__((used)) static void mga_dma_dispatch_indices(struct drm_device *dev, struct drm_buf *buf,
				     unsigned int start, unsigned int end)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_buf_priv_t *buf_priv = buf->dev_private;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	u32 address = (u32) buf->bus_address;
	int i = 0;
	DMA_LOCALS;
	DRM_DEBUG("buf=%d start=%d end=%d\n", buf->idx, start, end);

	if (start != end) {
		buf_priv->dispatched = 1;

		MGA_EMIT_STATE(dev_priv, sarea_priv->dirty);

		do {
			if (i < sarea_priv->nbox) {
				mga_emit_clip_rect(dev_priv,
						   &sarea_priv->boxes[i]);
			}

			BEGIN_DMA(1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_DMAPAD, 0x00000000,
				  MGA_SETUPADDRESS, address + start,
				  MGA_SETUPEND, ((address + end) |
						 dev_priv->dma_access));

			ADVANCE_DMA();
		} while (++i < sarea_priv->nbox);
	}

	if (buf_priv->discard) {
		AGE_BUFFER(buf_priv);
		buf->pending = 0;
		buf->used = 0;
		buf_priv->dispatched = 0;

		mga_freelist_put(dev, buf);
	}

	FLUSH_DMA();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_buf {int bus_address; scalar_t__ used; scalar_t__ pending; int /*<<< orphan*/  idx; TYPE_4__* dev_private; } ;
struct TYPE_7__ {int dma_access; int front_offset; int front_pitch; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_8__ {int plnwt; } ;
typedef  TYPE_3__ drm_mga_context_regs_t ;
struct TYPE_9__ {scalar_t__ dispatched; } ;
typedef  TYPE_4__ drm_mga_buf_priv_t ;
struct TYPE_6__ {TYPE_3__ context_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  AGE_BUFFER (TYPE_4__*) ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (scalar_t__,int,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FLUSH_DMA () ; 
 scalar_t__ MGA_AR0 ; 
 scalar_t__ MGA_AR3 ; 
 scalar_t__ MGA_AR5 ; 
 scalar_t__ MGA_DMAPAD ; 
 scalar_t__ MGA_DSTORG ; 
 scalar_t__ MGA_DWGCTL ; 
 int MGA_DWGCTL_COPY ; 
 scalar_t__ MGA_DWGSYNC ; 
 scalar_t__ MGA_EXEC ; 
 scalar_t__ MGA_FXBNDRY ; 
 scalar_t__ MGA_MACCESS ; 
 scalar_t__ MGA_PITCH ; 
 scalar_t__ MGA_PLNWT ; 
 int MGA_SRCMAP_SYSMEM ; 
 scalar_t__ MGA_SRCORG ; 
 scalar_t__ MGA_YDSTLEN ; 
 int /*<<< orphan*/  mga_freelist_put (struct drm_device*,struct drm_buf*) ; 

__attribute__((used)) static void mga_dma_dispatch_iload(struct drm_device *dev, struct drm_buf *buf,
				   unsigned int dstorg, unsigned int length)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_buf_priv_t *buf_priv = buf->dev_private;
	drm_mga_context_regs_t *ctx = &dev_priv->sarea_priv->context_state;
	u32 srcorg =
	    buf->bus_address | dev_priv->dma_access | MGA_SRCMAP_SYSMEM;
	u32 y2;
	DMA_LOCALS;
	DRM_DEBUG("buf=%d used=%d\n", buf->idx, buf->used);

	y2 = length / 64;

	BEGIN_DMA(5);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	DMA_BLOCK(MGA_DSTORG, dstorg,
		  MGA_MACCESS, 0x00000000, MGA_SRCORG, srcorg, MGA_AR5, 64);

	DMA_BLOCK(MGA_PITCH, 64,
		  MGA_PLNWT, 0xffffffff,
		  MGA_DMAPAD, 0x00000000, MGA_DWGCTL, MGA_DWGCTL_COPY);

	DMA_BLOCK(MGA_AR0, 63,
		  MGA_AR3, 0,
		  MGA_FXBNDRY, (63 << 16) | 0, MGA_YDSTLEN + MGA_EXEC, y2);

	DMA_BLOCK(MGA_PLNWT, ctx->plnwt,
		  MGA_SRCORG, dev_priv->front_offset,
		  MGA_PITCH, dev_priv->front_pitch, MGA_DWGSYNC, 0x00007000);

	ADVANCE_DMA();

	AGE_BUFFER(buf_priv);

	buf->pending = 0;
	buf->used = 0;
	buf_priv->dispatched = 0;

	mga_freelist_put(dev, buf);

	FLUSH_DMA();
}
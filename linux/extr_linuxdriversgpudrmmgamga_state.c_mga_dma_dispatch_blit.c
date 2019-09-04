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
struct drm_clip_rect {int x1; int y1; int y2; int x2; } ;
struct TYPE_8__ {int plnwt; int dwgctl; } ;
struct TYPE_6__ {int nbox; struct drm_clip_rect* boxes; TYPE_3__ context_state; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_7__ {int maccess; int front_pitch; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_context_regs_t ;
struct TYPE_9__ {int planemask; int srcorg; int dstorg; int ydir; int src_pitch; int dst_pitch; int delta_sx; int delta_sy; int delta_dx; int delta_dy; int height; } ;
typedef  TYPE_4__ drm_mga_blit_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (scalar_t__,int,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
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
 scalar_t__ MGA_SGN ; 
 scalar_t__ MGA_SRCORG ; 
 scalar_t__ MGA_YDSTLEN ; 

__attribute__((used)) static void mga_dma_dispatch_blit(struct drm_device *dev, drm_mga_blit_t *blit)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	int nbox = sarea_priv->nbox;
	u32 scandir = 0, i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_DMA(4 + nbox);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	DMA_BLOCK(MGA_DWGCTL, MGA_DWGCTL_COPY,
		  MGA_PLNWT, blit->planemask,
		  MGA_SRCORG, blit->srcorg, MGA_DSTORG, blit->dstorg);

	DMA_BLOCK(MGA_SGN, scandir,
		  MGA_MACCESS, dev_priv->maccess,
		  MGA_AR5, blit->ydir * blit->src_pitch,
		  MGA_PITCH, blit->dst_pitch);

	for (i = 0; i < nbox; i++) {
		int srcx = pbox[i].x1 + blit->delta_sx;
		int srcy = pbox[i].y1 + blit->delta_sy;
		int dstx = pbox[i].x1 + blit->delta_dx;
		int dsty = pbox[i].y1 + blit->delta_dy;
		int h = pbox[i].y2 - pbox[i].y1;
		int w = pbox[i].x2 - pbox[i].x1 - 1;
		int start;

		if (blit->ydir == -1)
			srcy = blit->height - srcy - 1;

		start = srcy * blit->src_pitch + srcx;

		DMA_BLOCK(MGA_AR0, start + w,
			  MGA_AR3, start,
			  MGA_FXBNDRY, ((dstx + w) << 16) | (dstx & 0xffff),
			  MGA_YDSTLEN + MGA_EXEC, (dsty << 16) | h);
	}

	/* Do something to flush AGP?
	 */

	/* Force reset of DWGCTL */
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, ctx->plnwt,
		  MGA_PITCH, dev_priv->front_pitch, MGA_DWGCTL, ctx->dwgctl);

	ADVANCE_DMA();
}
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
struct drm_clip_rect {int x2; int x1; unsigned int y1; int y2; } ;
struct TYPE_7__ {int dwgctl; } ;
struct TYPE_5__ {TYPE_3__ context_state; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_6__ {unsigned int front_pitch; scalar_t__ chipset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_context_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ ,unsigned int,scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 scalar_t__ MGA_CARD_TYPE_G400 ; 
 scalar_t__ MGA_CXBNDRY ; 
 int /*<<< orphan*/  MGA_DMAPAD ; 
 int /*<<< orphan*/  MGA_DWGCTL ; 
 scalar_t__ MGA_EXEC ; 
 scalar_t__ MGA_LEN ; 
 scalar_t__ MGA_YBOT ; 
 int /*<<< orphan*/  MGA_YTOP ; 

__attribute__((used)) static void mga_emit_clip_rect(drm_mga_private_t *dev_priv,
			       struct drm_clip_rect *box)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	unsigned int pitch = dev_priv->front_pitch;
	DMA_LOCALS;

	BEGIN_DMA(2);

	/* Force reset of DWGCTL on G400 (eliminates clip disable bit).
	 */
	if (dev_priv->chipset >= MGA_CARD_TYPE_G400) {
		DMA_BLOCK(MGA_DWGCTL, ctx->dwgctl,
			  MGA_LEN + MGA_EXEC, 0x80000000,
			  MGA_DWGCTL, ctx->dwgctl,
			  MGA_LEN + MGA_EXEC, 0x80000000);
	}
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_CXBNDRY, ((box->x2 - 1) << 16) | box->x1,
		  MGA_YTOP, box->y1 * pitch, MGA_YBOT, (box->y2 - 1) * pitch);

	ADVANCE_DMA();
}
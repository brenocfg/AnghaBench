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
struct TYPE_7__ {int maccess; int plnwt; int dwgctl; int fogcolor; int wflag; int /*<<< orphan*/  fcol; int /*<<< orphan*/  alphactrl; int /*<<< orphan*/  dstorg; } ;
struct TYPE_5__ {TYPE_3__ context_state; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_6__ {int depth_offset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_context_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  MGA_ALPHACTRL ; 
 int /*<<< orphan*/  MGA_DMAPAD ; 
 int /*<<< orphan*/  MGA_DSTORG ; 
 int /*<<< orphan*/  MGA_DWGCTL ; 
 int /*<<< orphan*/  MGA_FCOL ; 
 int /*<<< orphan*/  MGA_FOGCOL ; 
 int /*<<< orphan*/  MGA_MACCESS ; 
 int /*<<< orphan*/  MGA_PLNWT ; 
 int /*<<< orphan*/  MGA_WFLAG ; 
 int /*<<< orphan*/  MGA_ZORG ; 

__attribute__((used)) static __inline__ void mga_g200_emit_context(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	DMA_LOCALS;

	BEGIN_DMA(3);

	DMA_BLOCK(MGA_DSTORG, ctx->dstorg,
		  MGA_MACCESS, ctx->maccess,
		  MGA_PLNWT, ctx->plnwt, MGA_DWGCTL, ctx->dwgctl);

	DMA_BLOCK(MGA_ALPHACTRL, ctx->alphactrl,
		  MGA_FOGCOL, ctx->fogcolor,
		  MGA_WFLAG, ctx->wflag, MGA_ZORG, dev_priv->depth_offset);

	DMA_BLOCK(MGA_FCOL, ctx->fcol,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();
}
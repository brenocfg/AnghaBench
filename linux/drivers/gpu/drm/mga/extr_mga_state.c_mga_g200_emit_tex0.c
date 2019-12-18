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
struct TYPE_5__ {int texctl2; int texctl; int texfilter; int texbordercol; int texorg; int texorg1; int texorg2; int texorg3; int texorg4; int texwidth; int texheight; } ;
typedef  TYPE_1__ drm_mga_texture_regs_t ;
struct TYPE_6__ {TYPE_1__* tex_state; } ;
typedef  TYPE_2__ drm_mga_sarea_t ;
struct TYPE_7__ {TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  MGA_DMAPAD ; 
 int /*<<< orphan*/  MGA_TEXBORDERCOL ; 
 int /*<<< orphan*/  MGA_TEXCTL ; 
 int /*<<< orphan*/  MGA_TEXCTL2 ; 
 int /*<<< orphan*/  MGA_TEXFILTER ; 
 int /*<<< orphan*/  MGA_TEXHEIGHT ; 
 int /*<<< orphan*/  MGA_TEXORG ; 
 int /*<<< orphan*/  MGA_TEXORG1 ; 
 int /*<<< orphan*/  MGA_TEXORG2 ; 
 int /*<<< orphan*/  MGA_TEXORG3 ; 
 int /*<<< orphan*/  MGA_TEXORG4 ; 
 int /*<<< orphan*/  MGA_TEXTRANS ; 
 int /*<<< orphan*/  MGA_TEXTRANSHIGH ; 
 int /*<<< orphan*/  MGA_TEXWIDTH ; 
 int /*<<< orphan*/  MGA_WR24 ; 
 int /*<<< orphan*/  MGA_WR34 ; 

__attribute__((used)) static __inline__ void mga_g200_emit_tex0(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_texture_regs_t *tex = &sarea_priv->tex_state[0];
	DMA_LOCALS;

	BEGIN_DMA(4);

	DMA_BLOCK(MGA_TEXCTL2, tex->texctl2,
		  MGA_TEXCTL, tex->texctl,
		  MGA_TEXFILTER, tex->texfilter,
		  MGA_TEXBORDERCOL, tex->texbordercol);

	DMA_BLOCK(MGA_TEXORG, tex->texorg,
		  MGA_TEXORG1, tex->texorg1,
		  MGA_TEXORG2, tex->texorg2, MGA_TEXORG3, tex->texorg3);

	DMA_BLOCK(MGA_TEXORG4, tex->texorg4,
		  MGA_TEXWIDTH, tex->texwidth,
		  MGA_TEXHEIGHT, tex->texheight, MGA_WR24, tex->texwidth);

	DMA_BLOCK(MGA_WR34, tex->texheight,
		  MGA_TEXTRANS, 0x0000ffff,
		  MGA_TEXTRANSHIGH, 0x0000ffff, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();
}
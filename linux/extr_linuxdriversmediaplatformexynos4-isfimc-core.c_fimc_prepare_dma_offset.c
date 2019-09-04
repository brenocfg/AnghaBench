#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_8__ {int y_h; int y_v; int cb_h; int cb_v; int cr_h; int cr_v; } ;
struct fimc_frame {int offs_h; int offs_v; TYPE_4__ dma_offset; TYPE_3__* fmt; } ;
struct fimc_ctx {TYPE_2__* fimc_dev; } ;
struct TYPE_7__ {size_t memplanes; int colplanes; scalar_t__ color; scalar_t__* depth; } ;
struct TYPE_6__ {TYPE_1__* drv_data; } ;
struct TYPE_5__ {int dma_pix_hoff; } ;

/* Variables and functions */
 scalar_t__ FIMC_FMT_YCBCR420 ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,size_t,int) ; 

void fimc_prepare_dma_offset(struct fimc_ctx *ctx, struct fimc_frame *f)
{
	bool pix_hoff = ctx->fimc_dev->drv_data->dma_pix_hoff;
	u32 i, depth = 0;

	for (i = 0; i < f->fmt->memplanes; i++)
		depth += f->fmt->depth[i];

	f->dma_offset.y_h = f->offs_h;
	if (!pix_hoff)
		f->dma_offset.y_h *= (depth >> 3);

	f->dma_offset.y_v = f->offs_v;

	f->dma_offset.cb_h = f->offs_h;
	f->dma_offset.cb_v = f->offs_v;

	f->dma_offset.cr_h = f->offs_h;
	f->dma_offset.cr_v = f->offs_v;

	if (!pix_hoff) {
		if (f->fmt->colplanes == 3) {
			f->dma_offset.cb_h >>= 1;
			f->dma_offset.cr_h >>= 1;
		}
		if (f->fmt->color == FIMC_FMT_YCBCR420) {
			f->dma_offset.cb_v >>= 1;
			f->dma_offset.cr_v >>= 1;
		}
	}

	dbg("in_offset: color= %d, y_h= %d, y_v= %d",
	    f->fmt->color, f->dma_offset.y_h, f->dma_offset.y_v);
}
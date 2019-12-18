#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gsc_scaler {scalar_t__ range; } ;
struct gsc_context {scalar_t__ rotation; struct gsc_scaler sc; } ;
struct TYPE_6__ {scalar_t__ h; scalar_t__ w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int* pitch; int /*<<< orphan*/  height; } ;
struct exynos_drm_ipp_buffer {TYPE_3__ rect; TYPE_2__ buf; TYPE_1__* format; } ;
struct TYPE_4__ {int* cpp; } ;

/* Variables and functions */
 int GSC_DSTIMG_HEIGHT (int /*<<< orphan*/ ) ; 
 int GSC_DSTIMG_HEIGHT_MASK ; 
 int /*<<< orphan*/  GSC_DSTIMG_OFFSET ; 
 int GSC_DSTIMG_OFFSET_X (int /*<<< orphan*/ ) ; 
 int GSC_DSTIMG_OFFSET_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_DSTIMG_SIZE ; 
 int GSC_DSTIMG_WIDTH (int) ; 
 int GSC_DSTIMG_WIDTH_MASK ; 
 int /*<<< orphan*/  GSC_OUT_CON ; 
 int GSC_OUT_RGB_HD_NARROW ; 
 int GSC_OUT_RGB_HD_WIDE ; 
 int GSC_OUT_RGB_SD_NARROW ; 
 int GSC_OUT_RGB_SD_WIDE ; 
 int GSC_OUT_RGB_TYPE_MASK ; 
 int GSC_SCALED_HEIGHT (scalar_t__) ; 
 int /*<<< orphan*/  GSC_SCALED_SIZE ; 
 int GSC_SCALED_WIDTH (scalar_t__) ; 
 scalar_t__ GSC_WIDTH_ITU_709 ; 
 int gsc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsc_dst_set_size(struct gsc_context *ctx,
			     struct exynos_drm_ipp_buffer *buf)
{
	struct gsc_scaler *sc = &ctx->sc;
	u32 cfg;

	/* pixel offset */
	cfg = (GSC_DSTIMG_OFFSET_X(buf->rect.x) |
		GSC_DSTIMG_OFFSET_Y(buf->rect.y));
	gsc_write(cfg, GSC_DSTIMG_OFFSET);

	/* scaled size */
	if (ctx->rotation)
		cfg = (GSC_SCALED_WIDTH(buf->rect.h) |
		       GSC_SCALED_HEIGHT(buf->rect.w));
	else
		cfg = (GSC_SCALED_WIDTH(buf->rect.w) |
		       GSC_SCALED_HEIGHT(buf->rect.h));
	gsc_write(cfg, GSC_SCALED_SIZE);

	/* original size */
	cfg = gsc_read(GSC_DSTIMG_SIZE);
	cfg &= ~(GSC_DSTIMG_HEIGHT_MASK | GSC_DSTIMG_WIDTH_MASK);
	cfg |= GSC_DSTIMG_WIDTH(buf->buf.pitch[0] / buf->format->cpp[0]) |
	       GSC_DSTIMG_HEIGHT(buf->buf.height);
	gsc_write(cfg, GSC_DSTIMG_SIZE);

	cfg = gsc_read(GSC_OUT_CON);
	cfg &= ~GSC_OUT_RGB_TYPE_MASK;

	if (buf->rect.w >= GSC_WIDTH_ITU_709)
		if (sc->range)
			cfg |= GSC_OUT_RGB_HD_WIDE;
		else
			cfg |= GSC_OUT_RGB_HD_NARROW;
	else
		if (sc->range)
			cfg |= GSC_OUT_RGB_SD_WIDE;
		else
			cfg |= GSC_OUT_RGB_SD_NARROW;

	gsc_write(cfg, GSC_OUT_CON);
}
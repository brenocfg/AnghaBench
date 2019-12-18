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
struct fimc_context {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int w; int h; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {unsigned int* pitch; scalar_t__ width; int /*<<< orphan*/  height; } ;
struct exynos_drm_ipp_buffer {TYPE_3__ rect; TYPE_2__ buf; TYPE_1__* format; } ;
struct TYPE_4__ {unsigned int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  EXYNOS_CIGCTRL ; 
 int EXYNOS_CIGCTRL_CSC_ITU601 ; 
 int EXYNOS_CIGCTRL_CSC_ITU709 ; 
 int EXYNOS_CIGCTRL_CSC_MASK ; 
 int /*<<< orphan*/  EXYNOS_CIOCBOFF ; 
 int EXYNOS_CIOCBOFF_HORIZONTAL (int /*<<< orphan*/ ) ; 
 int EXYNOS_CIOCBOFF_VERTICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_CIOCROFF ; 
 int EXYNOS_CIOCROFF_HORIZONTAL (int /*<<< orphan*/ ) ; 
 int EXYNOS_CIOCROFF_VERTICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_CIOYOFF ; 
 int EXYNOS_CIOYOFF_HORIZONTAL (int /*<<< orphan*/ ) ; 
 int EXYNOS_CIOYOFF_VERTICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_CITAREA ; 
 int EXYNOS_CITAREA_TARGET_AREA (int) ; 
 int /*<<< orphan*/  EXYNOS_CITRGFMT ; 
 int EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE ; 
 int EXYNOS_CITRGFMT_TARGETHSIZE (int) ; 
 int EXYNOS_CITRGFMT_TARGETH_MASK ; 
 int EXYNOS_CITRGFMT_TARGETVSIZE (int) ; 
 int EXYNOS_CITRGFMT_TARGETV_MASK ; 
 int /*<<< orphan*/  EXYNOS_ORGOSIZE ; 
 int EXYNOS_ORGOSIZE_HORIZONTAL (unsigned int) ; 
 int EXYNOS_ORGOSIZE_VERTICAL (int /*<<< orphan*/ ) ; 
 scalar_t__ FIMC_WIDTH_ITU_709 ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_dst_set_size(struct fimc_context *ctx,
			     struct exynos_drm_ipp_buffer *buf)
{
	unsigned int real_width = buf->buf.pitch[0] / buf->format->cpp[0];
	u32 cfg, cfg_ext;

	DRM_DEV_DEBUG_KMS(ctx->dev, "hsize[%d]vsize[%d]\n", real_width,
			  buf->buf.height);

	/* original size */
	cfg = (EXYNOS_ORGOSIZE_HORIZONTAL(real_width) |
		EXYNOS_ORGOSIZE_VERTICAL(buf->buf.height));

	fimc_write(ctx, cfg, EXYNOS_ORGOSIZE);

	DRM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]\n", buf->rect.x,
			  buf->rect.y,
			  buf->rect.w, buf->rect.h);

	/* CSC ITU */
	cfg = fimc_read(ctx, EXYNOS_CIGCTRL);
	cfg &= ~EXYNOS_CIGCTRL_CSC_MASK;

	if (buf->buf.width >= FIMC_WIDTH_ITU_709)
		cfg |= EXYNOS_CIGCTRL_CSC_ITU709;
	else
		cfg |= EXYNOS_CIGCTRL_CSC_ITU601;

	fimc_write(ctx, cfg, EXYNOS_CIGCTRL);

	cfg_ext = fimc_read(ctx, EXYNOS_CITRGFMT);

	/* target image size */
	cfg = fimc_read(ctx, EXYNOS_CITRGFMT);
	cfg &= ~(EXYNOS_CITRGFMT_TARGETH_MASK |
		EXYNOS_CITRGFMT_TARGETV_MASK);
	if (cfg_ext & EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE)
		cfg |= (EXYNOS_CITRGFMT_TARGETHSIZE(buf->rect.h) |
			EXYNOS_CITRGFMT_TARGETVSIZE(buf->rect.w));
	else
		cfg |= (EXYNOS_CITRGFMT_TARGETHSIZE(buf->rect.w) |
			EXYNOS_CITRGFMT_TARGETVSIZE(buf->rect.h));
	fimc_write(ctx, cfg, EXYNOS_CITRGFMT);

	/* target area */
	cfg = EXYNOS_CITAREA_TARGET_AREA(buf->rect.w * buf->rect.h);
	fimc_write(ctx, cfg, EXYNOS_CITAREA);

	/* offset Y(RGB), Cb, Cr */
	cfg = (EXYNOS_CIOYOFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIOYOFF_VERTICAL(buf->rect.y));
	fimc_write(ctx, cfg, EXYNOS_CIOYOFF);
	cfg = (EXYNOS_CIOCBOFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIOCBOFF_VERTICAL(buf->rect.y));
	fimc_write(ctx, cfg, EXYNOS_CIOCBOFF);
	cfg = (EXYNOS_CIOCROFF_HORIZONTAL(buf->rect.x) |
		EXYNOS_CIOCROFF_VERTICAL(buf->rect.y));
	fimc_write(ctx, cfg, EXYNOS_CIOCROFF);
}
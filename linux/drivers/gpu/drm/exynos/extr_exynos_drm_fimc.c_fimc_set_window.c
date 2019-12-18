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
struct TYPE_6__ {unsigned int* pitch; int height; } ;
struct TYPE_5__ {int x; unsigned int w; int y; int h; } ;
struct exynos_drm_ipp_buffer {TYPE_3__ buf; TYPE_2__ rect; TYPE_1__* format; } ;
struct TYPE_4__ {unsigned int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,int,int,int,...) ; 
 int /*<<< orphan*/  EXYNOS_CIWDOFST ; 
 int /*<<< orphan*/  EXYNOS_CIWDOFST2 ; 
 int EXYNOS_CIWDOFST2_WINHOROFST2 (int) ; 
 int EXYNOS_CIWDOFST2_WINVEROFST2 (int) ; 
 int EXYNOS_CIWDOFST_WINHOROFST (int) ; 
 int EXYNOS_CIWDOFST_WINHOROFST_MASK ; 
 int EXYNOS_CIWDOFST_WINOFSEN ; 
 int EXYNOS_CIWDOFST_WINVEROFST (int) ; 
 int EXYNOS_CIWDOFST_WINVEROFST_MASK ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_set_window(struct fimc_context *ctx,
			    struct exynos_drm_ipp_buffer *buf)
{
	unsigned int real_width = buf->buf.pitch[0] / buf->format->cpp[0];
	u32 cfg, h1, h2, v1, v2;

	/* cropped image */
	h1 = buf->rect.x;
	h2 = real_width - buf->rect.w - buf->rect.x;
	v1 = buf->rect.y;
	v2 = buf->buf.height - buf->rect.h - buf->rect.y;

	DRM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]hsize[%d]vsize[%d]\n",
			  buf->rect.x, buf->rect.y, buf->rect.w, buf->rect.h,
			  real_width, buf->buf.height);
	DRM_DEV_DEBUG_KMS(ctx->dev, "h1[%d]h2[%d]v1[%d]v2[%d]\n", h1, h2, v1,
			  v2);

	/*
	 * set window offset 1, 2 size
	 * check figure 43-21 in user manual
	 */
	cfg = fimc_read(ctx, EXYNOS_CIWDOFST);
	cfg &= ~(EXYNOS_CIWDOFST_WINHOROFST_MASK |
		EXYNOS_CIWDOFST_WINVEROFST_MASK);
	cfg |= (EXYNOS_CIWDOFST_WINHOROFST(h1) |
		EXYNOS_CIWDOFST_WINVEROFST(v1));
	cfg |= EXYNOS_CIWDOFST_WINOFSEN;
	fimc_write(ctx, cfg, EXYNOS_CIWDOFST);

	cfg = (EXYNOS_CIWDOFST2_WINHOROFST2(h2) |
		EXYNOS_CIWDOFST2_WINVEROFST2(v2));
	fimc_write(ctx, cfg, EXYNOS_CIWDOFST2);
}
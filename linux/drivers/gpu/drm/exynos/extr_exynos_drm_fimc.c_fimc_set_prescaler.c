#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct fimc_scaler {int hratio; int vratio; int up_h; int up_v; } ;
struct fimc_context {int /*<<< orphan*/  dev; } ;
struct drm_exynos_ipp_task_rect {int h; int w; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXYNOS_CISCPREDST ; 
 int EXYNOS_CISCPREDST_PREDSTHEIGHT (int) ; 
 int EXYNOS_CISCPREDST_PREDSTWIDTH (int) ; 
 int /*<<< orphan*/  EXYNOS_CISCPRERATIO ; 
 int EXYNOS_CISCPRERATIO_PREHORRATIO (int) ; 
 int EXYNOS_CISCPRERATIO_PREVERRATIO (int) ; 
 int EXYNOS_CISCPRERATIO_SHFACTOR (int) ; 
 int /*<<< orphan*/  EXYNOS_CITRGFMT ; 
 int EXYNOS_CITRGFMT_INROT90_CLOCKWISE ; 
 int EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE ; 
 int FIMC_SHFACTOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 
 int fls (int) ; 

__attribute__((used)) static int fimc_set_prescaler(struct fimc_context *ctx, struct fimc_scaler *sc,
			      struct drm_exynos_ipp_task_rect *src,
			      struct drm_exynos_ipp_task_rect *dst)
{
	u32 cfg, cfg_ext, shfactor;
	u32 pre_dst_width, pre_dst_height;
	u32 hfactor, vfactor;
	int ret = 0;
	u32 src_w, src_h, dst_w, dst_h;

	cfg_ext = fimc_read(ctx, EXYNOS_CITRGFMT);
	if (cfg_ext & EXYNOS_CITRGFMT_INROT90_CLOCKWISE) {
		src_w = src->h;
		src_h = src->w;
	} else {
		src_w = src->w;
		src_h = src->h;
	}

	if (cfg_ext & EXYNOS_CITRGFMT_OUTROT90_CLOCKWISE) {
		dst_w = dst->h;
		dst_h = dst->w;
	} else {
		dst_w = dst->w;
		dst_h = dst->h;
	}

	/* fimc_ippdrv_check_property assures that dividers are not null */
	hfactor = fls(src_w / dst_w / 2);
	if (hfactor > FIMC_SHFACTOR / 2) {
		dev_err(ctx->dev, "failed to get ratio horizontal.\n");
		return -EINVAL;
	}

	vfactor = fls(src_h / dst_h / 2);
	if (vfactor > FIMC_SHFACTOR / 2) {
		dev_err(ctx->dev, "failed to get ratio vertical.\n");
		return -EINVAL;
	}

	pre_dst_width = src_w >> hfactor;
	pre_dst_height = src_h >> vfactor;
	DRM_DEV_DEBUG_KMS(ctx->dev, "pre_dst_width[%d]pre_dst_height[%d]\n",
			  pre_dst_width, pre_dst_height);
	DRM_DEV_DEBUG_KMS(ctx->dev, "hfactor[%d]vfactor[%d]\n", hfactor,
			  vfactor);

	sc->hratio = (src_w << 14) / (dst_w << hfactor);
	sc->vratio = (src_h << 14) / (dst_h << vfactor);
	sc->up_h = (dst_w >= src_w) ? true : false;
	sc->up_v = (dst_h >= src_h) ? true : false;
	DRM_DEV_DEBUG_KMS(ctx->dev, "hratio[%d]vratio[%d]up_h[%d]up_v[%d]\n",
			  sc->hratio, sc->vratio, sc->up_h, sc->up_v);

	shfactor = FIMC_SHFACTOR - (hfactor + vfactor);
	DRM_DEV_DEBUG_KMS(ctx->dev, "shfactor[%d]\n", shfactor);

	cfg = (EXYNOS_CISCPRERATIO_SHFACTOR(shfactor) |
		EXYNOS_CISCPRERATIO_PREHORRATIO(1 << hfactor) |
		EXYNOS_CISCPRERATIO_PREVERRATIO(1 << vfactor));
	fimc_write(ctx, cfg, EXYNOS_CISCPRERATIO);

	cfg = (EXYNOS_CISCPREDST_PREDSTWIDTH(pre_dst_width) |
		EXYNOS_CISCPREDST_PREDSTHEIGHT(pre_dst_height));
	fimc_write(ctx, cfg, EXYNOS_CISCPREDST);

	return ret;
}
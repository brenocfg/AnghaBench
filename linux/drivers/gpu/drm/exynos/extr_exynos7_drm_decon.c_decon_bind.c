#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct exynos_drm_plane {int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
struct decon_context {scalar_t__ encoder; int /*<<< orphan*/  crtc; struct exynos_drm_plane* planes; TYPE_1__* configs; } ;
struct TYPE_2__ {unsigned int zpos; int /*<<< orphan*/  type; int /*<<< orphan*/  num_pixel_formats; int /*<<< orphan*/  pixel_formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t DEFAULT_WIN ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int /*<<< orphan*/  EXYNOS_DISPLAY_TYPE_LCD ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int WINDOWS_NR ; 
 int /*<<< orphan*/  decon_crtc_ops ; 
 int decon_ctx_initialize (struct decon_context*,struct drm_device*) ; 
 int /*<<< orphan*/  decon_ctx_remove (struct decon_context*) ; 
 int /*<<< orphan*/  decon_formats ; 
 int /*<<< orphan*/ * decon_win_types ; 
 struct decon_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  exynos_dpi_bind (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  exynos_drm_crtc_create (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct decon_context*) ; 
 int exynos_plane_init (struct drm_device*,struct exynos_drm_plane*,unsigned int,TYPE_1__*) ; 

__attribute__((used)) static int decon_bind(struct device *dev, struct device *master, void *data)
{
	struct decon_context *ctx = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_plane *exynos_plane;
	unsigned int i;
	int ret;

	ret = decon_ctx_initialize(ctx, drm_dev);
	if (ret) {
		DRM_DEV_ERROR(dev, "decon_ctx_initialize failed.\n");
		return ret;
	}

	for (i = 0; i < WINDOWS_NR; i++) {
		ctx->configs[i].pixel_formats = decon_formats;
		ctx->configs[i].num_pixel_formats = ARRAY_SIZE(decon_formats);
		ctx->configs[i].zpos = i;
		ctx->configs[i].type = decon_win_types[i];

		ret = exynos_plane_init(drm_dev, &ctx->planes[i], i,
					&ctx->configs[i]);
		if (ret)
			return ret;
	}

	exynos_plane = &ctx->planes[DEFAULT_WIN];
	ctx->crtc = exynos_drm_crtc_create(drm_dev, &exynos_plane->base,
			EXYNOS_DISPLAY_TYPE_LCD, &decon_crtc_ops, ctx);
	if (IS_ERR(ctx->crtc)) {
		decon_ctx_remove(ctx);
		return PTR_ERR(ctx->crtc);
	}

	if (ctx->encoder)
		exynos_dpi_bind(drm_dev, ctx->encoder);

	return 0;

}
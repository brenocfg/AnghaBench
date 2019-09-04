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
struct platform_device {int dummy; } ;
struct drm_device {TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct ade_plane {int ch; int /*<<< orphan*/  base; struct ade_hw_ctx* ctx; } ;
struct ade_hw_ctx {int /*<<< orphan*/  irq; } ;
struct ade_crtc {int /*<<< orphan*/  base; int /*<<< orphan*/  out_format; struct ade_hw_ctx* ctx; } ;
struct ade_data {struct ade_plane* aplane; struct ade_crtc acrtc; struct ade_hw_ctx ctx; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ADE_CH_NUM ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  LDI_OUT_RGB_888 ; 
 int PRIMARY_CH ; 
 int ade_crtc_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ade_dts_parse (struct platform_device*,struct ade_hw_ctx*) ; 
 int /*<<< orphan*/  ade_irq_handler ; 
 int ade_plane_init (struct drm_device*,struct ade_plane*,int) ; 
 struct ade_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ade_crtc*) ; 
 struct drm_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ade_data*) ; 

__attribute__((used)) static int ade_drm_init(struct platform_device *pdev)
{
	struct drm_device *dev = platform_get_drvdata(pdev);
	struct ade_data *ade;
	struct ade_hw_ctx *ctx;
	struct ade_crtc *acrtc;
	struct ade_plane *aplane;
	enum drm_plane_type type;
	int ret;
	int i;

	ade = devm_kzalloc(dev->dev, sizeof(*ade), GFP_KERNEL);
	if (!ade) {
		DRM_ERROR("failed to alloc ade_data\n");
		return -ENOMEM;
	}
	platform_set_drvdata(pdev, ade);

	ctx = &ade->ctx;
	acrtc = &ade->acrtc;
	acrtc->ctx = ctx;
	acrtc->out_format = LDI_OUT_RGB_888;

	ret = ade_dts_parse(pdev, ctx);
	if (ret)
		return ret;

	/*
	 * plane init
	 * TODO: Now only support primary plane, overlay planes
	 * need to do.
	 */
	for (i = 0; i < ADE_CH_NUM; i++) {
		aplane = &ade->aplane[i];
		aplane->ch = i;
		aplane->ctx = ctx;
		type = i == PRIMARY_CH ? DRM_PLANE_TYPE_PRIMARY :
			DRM_PLANE_TYPE_OVERLAY;

		ret = ade_plane_init(dev, aplane, type);
		if (ret)
			return ret;
	}

	/* crtc init */
	ret = ade_crtc_init(dev, &acrtc->base, &ade->aplane[PRIMARY_CH].base);
	if (ret)
		return ret;

	/* vblank irq init */
	ret = devm_request_irq(dev->dev, ctx->irq, ade_irq_handler,
			       IRQF_SHARED, dev->driver->name, acrtc);
	if (ret)
		return ret;

	return 0;
}
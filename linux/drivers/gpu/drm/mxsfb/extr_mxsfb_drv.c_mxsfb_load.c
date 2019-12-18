#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {TYPE_1__* id_entry; int /*<<< orphan*/  dev; } ;
struct mxsfb_drm_private {int /*<<< orphan*/  panel; int /*<<< orphan*/  connector; int /*<<< orphan*/  pipe; int /*<<< orphan*/ * clk_disp_axi; int /*<<< orphan*/ * clk_axi; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * base; int /*<<< orphan*/ * devdata; } ;
struct TYPE_4__ {int /*<<< orphan*/ * helper_private; int /*<<< orphan*/ * funcs; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_2__ mode_config; struct mxsfb_drm_private* dev_private; } ;
struct TYPE_3__ {size_t driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MXSFB_MAX_XRES ; 
 int /*<<< orphan*/  MXSFB_MAX_YRES ; 
 int /*<<< orphan*/  MXSFB_MIN_XRES ; 
 int /*<<< orphan*/  MXSFB_MIN_YRES ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 struct mxsfb_drm_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (struct drm_device*) ; 
 int drm_irq_install (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_panel_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_detach (int /*<<< orphan*/ ) ; 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int mxsfb_create_output (struct drm_device*) ; 
 int /*<<< orphan*/ * mxsfb_devdata ; 
 int /*<<< orphan*/  mxsfb_formats ; 
 int /*<<< orphan*/  mxsfb_funcs ; 
 int /*<<< orphan*/  mxsfb_mode_config_funcs ; 
 int /*<<< orphan*/  mxsfb_mode_config_helpers ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxsfb_load(struct drm_device *drm, unsigned long flags)
{
	struct platform_device *pdev = to_platform_device(drm->dev);
	struct mxsfb_drm_private *mxsfb;
	struct resource *res;
	int ret;

	mxsfb = devm_kzalloc(&pdev->dev, sizeof(*mxsfb), GFP_KERNEL);
	if (!mxsfb)
		return -ENOMEM;

	drm->dev_private = mxsfb;
	mxsfb->devdata = &mxsfb_devdata[pdev->id_entry->driver_data];

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mxsfb->base = devm_ioremap_resource(drm->dev, res);
	if (IS_ERR(mxsfb->base))
		return PTR_ERR(mxsfb->base);

	mxsfb->clk = devm_clk_get(drm->dev, NULL);
	if (IS_ERR(mxsfb->clk))
		return PTR_ERR(mxsfb->clk);

	mxsfb->clk_axi = devm_clk_get(drm->dev, "axi");
	if (IS_ERR(mxsfb->clk_axi))
		mxsfb->clk_axi = NULL;

	mxsfb->clk_disp_axi = devm_clk_get(drm->dev, "disp_axi");
	if (IS_ERR(mxsfb->clk_disp_axi))
		mxsfb->clk_disp_axi = NULL;

	ret = dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	pm_runtime_enable(drm->dev);

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	if (ret < 0) {
		dev_err(drm->dev, "Failed to initialise vblank\n");
		goto err_vblank;
	}

	/* Modeset init */
	drm_mode_config_init(drm);

	ret = mxsfb_create_output(drm);
	if (ret < 0) {
		dev_err(drm->dev, "Failed to create outputs\n");
		goto err_vblank;
	}

	ret = drm_simple_display_pipe_init(drm, &mxsfb->pipe, &mxsfb_funcs,
			mxsfb_formats, ARRAY_SIZE(mxsfb_formats), NULL,
			&mxsfb->connector);
	if (ret < 0) {
		dev_err(drm->dev, "Cannot setup simple display pipe\n");
		goto err_vblank;
	}

	ret = drm_panel_attach(mxsfb->panel, &mxsfb->connector);
	if (ret) {
		dev_err(drm->dev, "Cannot connect panel\n");
		goto err_vblank;
	}

	drm->mode_config.min_width	= MXSFB_MIN_XRES;
	drm->mode_config.min_height	= MXSFB_MIN_YRES;
	drm->mode_config.max_width	= MXSFB_MAX_XRES;
	drm->mode_config.max_height	= MXSFB_MAX_YRES;
	drm->mode_config.funcs		= &mxsfb_mode_config_funcs;
	drm->mode_config.helper_private	= &mxsfb_mode_config_helpers;

	drm_mode_config_reset(drm);

	pm_runtime_get_sync(drm->dev);
	ret = drm_irq_install(drm, platform_get_irq(pdev, 0));
	pm_runtime_put_sync(drm->dev);

	if (ret < 0) {
		dev_err(drm->dev, "Failed to install IRQ handler\n");
		goto err_irq;
	}

	drm_kms_helper_poll_init(drm);

	platform_set_drvdata(pdev, drm);

	drm_helper_hpd_irq_event(drm);

	return 0;

err_irq:
	drm_panel_detach(mxsfb->panel);
err_vblank:
	pm_runtime_disable(drm->dev);

	return ret;
}
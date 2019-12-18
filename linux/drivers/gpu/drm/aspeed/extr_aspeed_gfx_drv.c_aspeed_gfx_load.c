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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct drm_device {int /*<<< orphan*/ * dev; struct aspeed_gfx* dev_private; } ;
struct aspeed_gfx {scalar_t__ base; scalar_t__ clk; scalar_t__ rst; scalar_t__ scu; } ;

/* Variables and functions */
 scalar_t__ CRT_CTRL1 ; 
 scalar_t__ CRT_CTRL2 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int aspeed_gfx_create_output (struct drm_device*) ; 
 int aspeed_gfx_create_pipe (struct drm_device*) ; 
 int /*<<< orphan*/  aspeed_gfx_irq_handler ; 
 int /*<<< orphan*/  aspeed_gfx_setup_mode_config (struct drm_device*) ; 
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct aspeed_gfx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct drm_device*) ; 
 scalar_t__ devm_reset_control_get_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 int of_reserved_mem_device_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (scalar_t__) ; 
 scalar_t__ syscon_regmap_lookup_by_compatible (char*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aspeed_gfx_load(struct drm_device *drm)
{
	struct platform_device *pdev = to_platform_device(drm->dev);
	struct aspeed_gfx *priv;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	drm->dev_private = priv;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(drm->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->scu = syscon_regmap_lookup_by_compatible("aspeed,ast2500-scu");
	if (IS_ERR(priv->scu)) {
		dev_err(&pdev->dev, "failed to find SCU regmap\n");
		return PTR_ERR(priv->scu);
	}

	ret = of_reserved_mem_device_init(drm->dev);
	if (ret) {
		dev_err(&pdev->dev,
			"failed to initialize reserved mem: %d\n", ret);
		return ret;
	}

	ret = dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", ret);
		return ret;
	}

	priv->rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(priv->rst)) {
		dev_err(&pdev->dev,
			"missing or invalid reset controller device tree entry");
		return PTR_ERR(priv->rst);
	}
	reset_control_deassert(priv->rst);

	priv->clk = devm_clk_get(drm->dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev,
			"missing or invalid clk device tree entry");
		return PTR_ERR(priv->clk);
	}
	clk_prepare_enable(priv->clk);

	/* Sanitize control registers */
	writel(0, priv->base + CRT_CTRL1);
	writel(0, priv->base + CRT_CTRL2);

	aspeed_gfx_setup_mode_config(drm);

	ret = drm_vblank_init(drm, 1);
	if (ret < 0) {
		dev_err(drm->dev, "Failed to initialise vblank\n");
		return ret;
	}

	ret = aspeed_gfx_create_output(drm);
	if (ret < 0) {
		dev_err(drm->dev, "Failed to create outputs\n");
		return ret;
	}

	ret = aspeed_gfx_create_pipe(drm);
	if (ret < 0) {
		dev_err(drm->dev, "Cannot setup simple display pipe\n");
		return ret;
	}

	ret = devm_request_irq(drm->dev, platform_get_irq(pdev, 0),
			       aspeed_gfx_irq_handler, 0, "aspeed gfx", drm);
	if (ret < 0) {
		dev_err(drm->dev, "Failed to install IRQ handler\n");
		return ret;
	}

	drm_mode_config_reset(drm);

	drm_fbdev_generic_setup(drm, 32);

	return 0;
}
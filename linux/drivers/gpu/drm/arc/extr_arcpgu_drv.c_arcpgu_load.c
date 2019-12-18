#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct drm_device {TYPE_1__* dev; struct arcpgu_drm_private* dev_private; } ;
struct device_node {int dummy; } ;
struct arcpgu_drm_private {int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCPGU_REG_ID ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_pgu_read (struct arcpgu_drm_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ arc_pgu_setup_crtc (struct drm_device*) ; 
 int arcpgu_drm_hdmi_init (struct drm_device*,struct device_node*) ; 
 int arcpgu_drm_sim_init (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arcpgu_setup_mode_config (struct drm_device*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct arcpgu_drm_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_set_mask_and_coherent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_reserved_mem_device_init (TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 
 struct platform_device* to_platform_device (TYPE_1__*) ; 

__attribute__((used)) static int arcpgu_load(struct drm_device *drm)
{
	struct platform_device *pdev = to_platform_device(drm->dev);
	struct arcpgu_drm_private *arcpgu;
	struct device_node *encoder_node;
	struct resource *res;
	int ret;

	arcpgu = devm_kzalloc(&pdev->dev, sizeof(*arcpgu), GFP_KERNEL);
	if (arcpgu == NULL)
		return -ENOMEM;

	drm->dev_private = arcpgu;

	arcpgu->clk = devm_clk_get(drm->dev, "pxlclk");
	if (IS_ERR(arcpgu->clk))
		return PTR_ERR(arcpgu->clk);

	arcpgu_setup_mode_config(drm);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	arcpgu->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(arcpgu->regs))
		return PTR_ERR(arcpgu->regs);

	dev_info(drm->dev, "arc_pgu ID: 0x%x\n",
		 arc_pgu_read(arcpgu, ARCPGU_REG_ID));

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(drm->dev);
	if (ret && ret != -ENODEV)
		return ret;

	if (dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32)))
		return -ENODEV;

	if (arc_pgu_setup_crtc(drm) < 0)
		return -ENODEV;

	/* find the encoder node and initialize it */
	encoder_node = of_parse_phandle(drm->dev->of_node, "encoder-slave", 0);
	if (encoder_node) {
		ret = arcpgu_drm_hdmi_init(drm, encoder_node);
		of_node_put(encoder_node);
		if (ret < 0)
			return ret;
	} else {
		ret = arcpgu_drm_sim_init(drm, NULL);
		if (ret < 0)
			return ret;
	}

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	platform_set_drvdata(pdev, drm);
	return 0;
}
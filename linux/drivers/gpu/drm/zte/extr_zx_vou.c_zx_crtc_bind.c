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
struct zx_vou_hw {void* axi_clk; void* ppu_clk; struct device* dev; void* otfppu; void* vouctl; void* dtrc; void* timing; void* osd; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  VOU_CHN_AUX ; 
 int /*<<< orphan*/  VOU_CHN_MAIN ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct zx_vou_hw*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct zx_vou_hw* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct zx_vou_hw*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vou_hw_init (struct zx_vou_hw*) ; 
 int /*<<< orphan*/  vou_irq_handler ; 
 int zx_crtc_init (struct drm_device*,struct zx_vou_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_overlay_init (struct drm_device*,struct zx_vou_hw*) ; 

__attribute__((used)) static int zx_crtc_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = data;
	struct zx_vou_hw *vou;
	struct resource *res;
	int irq;
	int ret;

	vou = devm_kzalloc(dev, sizeof(*vou), GFP_KERNEL);
	if (!vou)
		return -ENOMEM;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "osd");
	vou->osd = devm_ioremap_resource(dev, res);
	if (IS_ERR(vou->osd)) {
		ret = PTR_ERR(vou->osd);
		DRM_DEV_ERROR(dev, "failed to remap osd region: %d\n", ret);
		return ret;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "timing_ctrl");
	vou->timing = devm_ioremap_resource(dev, res);
	if (IS_ERR(vou->timing)) {
		ret = PTR_ERR(vou->timing);
		DRM_DEV_ERROR(dev, "failed to remap timing_ctrl region: %d\n",
			      ret);
		return ret;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dtrc");
	vou->dtrc = devm_ioremap_resource(dev, res);
	if (IS_ERR(vou->dtrc)) {
		ret = PTR_ERR(vou->dtrc);
		DRM_DEV_ERROR(dev, "failed to remap dtrc region: %d\n", ret);
		return ret;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "vou_ctrl");
	vou->vouctl = devm_ioremap_resource(dev, res);
	if (IS_ERR(vou->vouctl)) {
		ret = PTR_ERR(vou->vouctl);
		DRM_DEV_ERROR(dev, "failed to remap vou_ctrl region: %d\n",
			      ret);
		return ret;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "otfppu");
	vou->otfppu = devm_ioremap_resource(dev, res);
	if (IS_ERR(vou->otfppu)) {
		ret = PTR_ERR(vou->otfppu);
		DRM_DEV_ERROR(dev, "failed to remap otfppu region: %d\n", ret);
		return ret;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	vou->axi_clk = devm_clk_get(dev, "aclk");
	if (IS_ERR(vou->axi_clk)) {
		ret = PTR_ERR(vou->axi_clk);
		DRM_DEV_ERROR(dev, "failed to get axi_clk: %d\n", ret);
		return ret;
	}

	vou->ppu_clk = devm_clk_get(dev, "ppu_wclk");
	if (IS_ERR(vou->ppu_clk)) {
		ret = PTR_ERR(vou->ppu_clk);
		DRM_DEV_ERROR(dev, "failed to get ppu_clk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(vou->axi_clk);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to enable axi_clk: %d\n", ret);
		return ret;
	}

	clk_prepare_enable(vou->ppu_clk);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to enable ppu_clk: %d\n", ret);
		goto disable_axi_clk;
	}

	vou->dev = dev;
	dev_set_drvdata(dev, vou);

	vou_hw_init(vou);

	ret = devm_request_irq(dev, irq, vou_irq_handler, 0, "zx_vou", vou);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "failed to request vou irq: %d\n", ret);
		goto disable_ppu_clk;
	}

	ret = zx_crtc_init(drm, vou, VOU_CHN_MAIN);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to init main channel crtc: %d\n",
			      ret);
		goto disable_ppu_clk;
	}

	ret = zx_crtc_init(drm, vou, VOU_CHN_AUX);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to init aux channel crtc: %d\n",
			      ret);
		goto disable_ppu_clk;
	}

	zx_overlay_init(drm, vou);

	return 0;

disable_ppu_clk:
	clk_disable_unprepare(vou->ppu_clk);
disable_axi_clk:
	clk_disable_unprepare(vou->axi_clk);
	return ret;
}
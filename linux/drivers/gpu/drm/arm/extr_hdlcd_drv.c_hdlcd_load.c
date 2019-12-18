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
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct hdlcd_drm_private {int /*<<< orphan*/  crtc; int /*<<< orphan*/ * mmio; int /*<<< orphan*/  dma_end_count; int /*<<< orphan*/  vsync_count; int /*<<< orphan*/  bus_error_count; int /*<<< orphan*/  buffer_underrun_count; int /*<<< orphan*/ * clk; } ;
struct drm_device {int /*<<< orphan*/  dev; struct hdlcd_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int HDLCD_PRODUCT_ID ; 
 int HDLCD_PRODUCT_MASK ; 
 int /*<<< orphan*/  HDLCD_REG_VERSION ; 
 int HDLCD_VERSION_MAJOR_MASK ; 
 int HDLCD_VERSION_MINOR_MASK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_cleanup (int /*<<< orphan*/ *) ; 
 int drm_irq_install (struct drm_device*,int /*<<< orphan*/ ) ; 
 int hdlcd_read (struct hdlcd_drm_private*,int /*<<< orphan*/ ) ; 
 int hdlcd_setup_crtc (struct drm_device*) ; 
 int of_reserved_mem_device_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdlcd_load(struct drm_device *drm, unsigned long flags)
{
	struct hdlcd_drm_private *hdlcd = drm->dev_private;
	struct platform_device *pdev = to_platform_device(drm->dev);
	struct resource *res;
	u32 version;
	int ret;

	hdlcd->clk = devm_clk_get(drm->dev, "pxlclk");
	if (IS_ERR(hdlcd->clk))
		return PTR_ERR(hdlcd->clk);

#ifdef CONFIG_DEBUG_FS
	atomic_set(&hdlcd->buffer_underrun_count, 0);
	atomic_set(&hdlcd->bus_error_count, 0);
	atomic_set(&hdlcd->vsync_count, 0);
	atomic_set(&hdlcd->dma_end_count, 0);
#endif

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hdlcd->mmio = devm_ioremap_resource(drm->dev, res);
	if (IS_ERR(hdlcd->mmio)) {
		DRM_ERROR("failed to map control registers area\n");
		ret = PTR_ERR(hdlcd->mmio);
		hdlcd->mmio = NULL;
		return ret;
	}

	version = hdlcd_read(hdlcd, HDLCD_REG_VERSION);
	if ((version & HDLCD_PRODUCT_MASK) != HDLCD_PRODUCT_ID) {
		DRM_ERROR("unknown product id: 0x%x\n", version);
		return -EINVAL;
	}
	DRM_INFO("found ARM HDLCD version r%dp%d\n",
		(version & HDLCD_VERSION_MAJOR_MASK) >> 8,
		version & HDLCD_VERSION_MINOR_MASK);

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(drm->dev);
	if (ret && ret != -ENODEV)
		return ret;

	ret = dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32));
	if (ret)
		goto setup_fail;

	ret = hdlcd_setup_crtc(drm);
	if (ret < 0) {
		DRM_ERROR("failed to create crtc\n");
		goto setup_fail;
	}

	ret = drm_irq_install(drm, platform_get_irq(pdev, 0));
	if (ret < 0) {
		DRM_ERROR("failed to install IRQ handler\n");
		goto irq_fail;
	}

	return 0;

irq_fail:
	drm_crtc_cleanup(&hdlcd->crtc);
setup_fail:
	of_reserved_mem_device_release(drm->dev);

	return ret;
}
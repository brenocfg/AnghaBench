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
struct zx_tvenc {int /*<<< orphan*/  mmio; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct zx_tvenc*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct zx_tvenc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int zx_tvenc_pwrctrl_init (struct zx_tvenc*) ; 
 int zx_tvenc_register (struct drm_device*,struct zx_tvenc*) ; 

__attribute__((used)) static int zx_tvenc_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = data;
	struct resource *res;
	struct zx_tvenc *tvenc;
	int ret;

	tvenc = devm_kzalloc(dev, sizeof(*tvenc), GFP_KERNEL);
	if (!tvenc)
		return -ENOMEM;

	tvenc->dev = dev;
	dev_set_drvdata(dev, tvenc);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	tvenc->mmio = devm_ioremap_resource(dev, res);
	if (IS_ERR(tvenc->mmio)) {
		ret = PTR_ERR(tvenc->mmio);
		DRM_DEV_ERROR(dev, "failed to remap tvenc region: %d\n", ret);
		return ret;
	}

	ret = zx_tvenc_pwrctrl_init(tvenc);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to init power control: %d\n", ret);
		return ret;
	}

	ret = zx_tvenc_register(drm, tvenc);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to register tvenc: %d\n", ret);
		return ret;
	}

	return 0;
}
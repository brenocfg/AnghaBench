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
struct vop_data {int feature; int /*<<< orphan*/  win_size; } ;
struct vop {unsigned int irq; int /*<<< orphan*/  rgb; struct drm_device* drm_dev; int /*<<< orphan*/  crtc; struct vop_data const* data; int /*<<< orphan*/  vop_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  reg_lock; void* regsbak; int /*<<< orphan*/  len; int /*<<< orphan*/  regs; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int VOP_FEATURE_INTERNAL_RGB ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vop*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vop*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct vop_data* of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  rockchip_rgb_init (struct device*,int /*<<< orphan*/ *,struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int vop_create_crtc (struct vop*) ; 
 int /*<<< orphan*/  vop_destroy_crtc (struct vop*) ; 
 int vop_initial (struct vop*) ; 
 int /*<<< orphan*/  vop_isr ; 
 int /*<<< orphan*/  vop_win_init (struct vop*) ; 
 int /*<<< orphan*/  win ; 

__attribute__((used)) static int vop_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	const struct vop_data *vop_data;
	struct drm_device *drm_dev = data;
	struct vop *vop;
	struct resource *res;
	int ret, irq;

	vop_data = of_device_get_match_data(dev);
	if (!vop_data)
		return -ENODEV;

	/* Allocate vop struct and its vop_win array */
	vop = devm_kzalloc(dev, struct_size(vop, win, vop_data->win_size),
			   GFP_KERNEL);
	if (!vop)
		return -ENOMEM;

	vop->dev = dev;
	vop->data = vop_data;
	vop->drm_dev = drm_dev;
	dev_set_drvdata(dev, vop);

	vop_win_init(vop);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vop->len = resource_size(res);
	vop->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(vop->regs))
		return PTR_ERR(vop->regs);

	vop->regsbak = devm_kzalloc(dev, vop->len, GFP_KERNEL);
	if (!vop->regsbak)
		return -ENOMEM;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		DRM_DEV_ERROR(dev, "cannot find irq for vop\n");
		return irq;
	}
	vop->irq = (unsigned int)irq;

	spin_lock_init(&vop->reg_lock);
	spin_lock_init(&vop->irq_lock);
	mutex_init(&vop->vop_lock);

	ret = vop_create_crtc(vop);
	if (ret)
		return ret;

	pm_runtime_enable(&pdev->dev);

	ret = vop_initial(vop);
	if (ret < 0) {
		DRM_DEV_ERROR(&pdev->dev,
			      "cannot initial vop dev - err %d\n", ret);
		goto err_disable_pm_runtime;
	}

	ret = devm_request_irq(dev, vop->irq, vop_isr,
			       IRQF_SHARED, dev_name(dev), vop);
	if (ret)
		goto err_disable_pm_runtime;

	if (vop->data->feature & VOP_FEATURE_INTERNAL_RGB) {
		vop->rgb = rockchip_rgb_init(dev, &vop->crtc, vop->drm_dev);
		if (IS_ERR(vop->rgb)) {
			ret = PTR_ERR(vop->rgb);
			goto err_disable_pm_runtime;
		}
	}

	return 0;

err_disable_pm_runtime:
	pm_runtime_disable(&pdev->dev);
	vop_destroy_crtc(vop);
	return ret;
}
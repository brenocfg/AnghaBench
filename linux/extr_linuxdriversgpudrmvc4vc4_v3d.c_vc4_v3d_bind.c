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
struct vc4_v3d {int /*<<< orphan*/ * clk; struct vc4_dev* vc4; int /*<<< orphan*/ * regs; struct platform_device* pdev; } ;
struct vc4_dev {struct vc4_v3d* v3d; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V3D_BPOA ; 
 int /*<<< orphan*/  V3D_BPOS ; 
 scalar_t__ V3D_EXPECTED_IDENT0 ; 
 int /*<<< orphan*/  V3D_IDENT0 ; 
 scalar_t__ V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vc4_v3d*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct vc4_v3d* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int drm_irq_install (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int vc4_allocate_bin_bo (struct drm_device*) ; 
 int /*<<< orphan*/ * vc4_ioremap_regs (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_v3d_init_hw (struct drm_device*) ; 

__attribute__((used)) static int vc4_v3d_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	struct vc4_v3d *v3d = NULL;
	int ret;

	v3d = devm_kzalloc(&pdev->dev, sizeof(*v3d), GFP_KERNEL);
	if (!v3d)
		return -ENOMEM;

	dev_set_drvdata(dev, v3d);

	v3d->pdev = pdev;

	v3d->regs = vc4_ioremap_regs(pdev, 0);
	if (IS_ERR(v3d->regs))
		return PTR_ERR(v3d->regs);

	vc4->v3d = v3d;
	v3d->vc4 = vc4;

	v3d->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(v3d->clk)) {
		int ret = PTR_ERR(v3d->clk);

		if (ret == -ENOENT) {
			/* bcm2835 didn't have a clock reference in the DT. */
			ret = 0;
			v3d->clk = NULL;
		} else {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get V3D clock: %d\n",
					ret);
			return ret;
		}
	}

	if (V3D_READ(V3D_IDENT0) != V3D_EXPECTED_IDENT0) {
		DRM_ERROR("V3D_IDENT0 read 0x%08x instead of 0x%08x\n",
			  V3D_READ(V3D_IDENT0), V3D_EXPECTED_IDENT0);
		return -EINVAL;
	}

	ret = clk_prepare_enable(v3d->clk);
	if (ret != 0)
		return ret;

	ret = vc4_allocate_bin_bo(drm);
	if (ret) {
		clk_disable_unprepare(v3d->clk);
		return ret;
	}

	/* Reset the binner overflow address/size at setup, to be sure
	 * we don't reuse an old one.
	 */
	V3D_WRITE(V3D_BPOA, 0);
	V3D_WRITE(V3D_BPOS, 0);

	vc4_v3d_init_hw(drm);

	ret = drm_irq_install(drm, platform_get_irq(pdev, 0));
	if (ret) {
		DRM_ERROR("Failed to install IRQ handler\n");
		return ret;
	}

	pm_runtime_set_active(dev);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, 40); /* a little over 2 frames. */
	pm_runtime_enable(dev);

	return 0;
}
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
struct venc_device {int requires_tv_dac_clk; int /*<<< orphan*/  vdda_dac_reg; int /*<<< orphan*/  base; struct platform_device* pdev; int /*<<< orphan*/ * config; int /*<<< orphan*/  venc_lock; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int component_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct venc_device*) ; 
 struct venc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct venc_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_component_ops ; 
 int /*<<< orphan*/  venc_config_pal_trm ; 
 int venc_get_clocks (struct venc_device*) ; 
 int venc_init_output (struct venc_device*) ; 
 int venc_probe_of (struct venc_device*) ; 
 int /*<<< orphan*/  venc_soc_devices ; 
 int /*<<< orphan*/  venc_uninit_output (struct venc_device*) ; 

__attribute__((used)) static int venc_probe(struct platform_device *pdev)
{
	struct venc_device *venc;
	struct resource *venc_mem;
	int r;

	venc = kzalloc(sizeof(*venc), GFP_KERNEL);
	if (!venc)
		return -ENOMEM;

	venc->pdev = pdev;

	platform_set_drvdata(pdev, venc);

	/* The OMAP34xx, OMAP35xx and AM35xx VENC require the TV DAC clock. */
	if (soc_device_match(venc_soc_devices))
		venc->requires_tv_dac_clk = true;

	mutex_init(&venc->venc_lock);

	venc->config = &venc_config_pal_trm;

	venc_mem = platform_get_resource(venc->pdev, IORESOURCE_MEM, 0);
	venc->base = devm_ioremap_resource(&pdev->dev, venc_mem);
	if (IS_ERR(venc->base)) {
		r = PTR_ERR(venc->base);
		goto err_free;
	}

	venc->vdda_dac_reg = devm_regulator_get(&pdev->dev, "vdda");
	if (IS_ERR(venc->vdda_dac_reg)) {
		r = PTR_ERR(venc->vdda_dac_reg);
		if (r != -EPROBE_DEFER)
			DSSERR("can't get VDDA_DAC regulator\n");
		goto err_free;
	}

	r = venc_get_clocks(venc);
	if (r)
		goto err_free;

	r = venc_probe_of(venc);
	if (r)
		goto err_free;

	pm_runtime_enable(&pdev->dev);

	r = venc_init_output(venc);
	if (r)
		goto err_pm_disable;

	r = component_add(&pdev->dev, &venc_component_ops);
	if (r)
		goto err_uninit_output;

	return 0;

err_uninit_output:
	venc_uninit_output(venc);
err_pm_disable:
	pm_runtime_disable(&pdev->dev);
err_free:
	kfree(venc);
	return r;
}
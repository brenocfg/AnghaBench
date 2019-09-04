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
typedef  scalar_t__ u8 ;
struct venc_device {int requires_tv_dac_clk; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  base; struct platform_device* pdev; scalar_t__ wss_data; int /*<<< orphan*/  venc_lock; struct dss_device* dss; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VENC_REV_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct venc_device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct venc_device*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct venc_device*) ; 
 struct venc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  venc_dump_regs ; 
 int venc_get_clocks (struct venc_device*) ; 
 int /*<<< orphan*/  venc_init_output (struct venc_device*) ; 
 int venc_probe_of (struct venc_device*) ; 
 int venc_read_reg (struct venc_device*,int /*<<< orphan*/ ) ; 
 int venc_runtime_get (struct venc_device*) ; 
 int /*<<< orphan*/  venc_runtime_put (struct venc_device*) ; 
 int /*<<< orphan*/  venc_soc_devices ; 

__attribute__((used)) static int venc_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct dss_device *dss = dss_get_device(master);
	struct venc_device *venc;
	u8 rev_id;
	struct resource *venc_mem;
	int r;

	venc = kzalloc(sizeof(*venc), GFP_KERNEL);
	if (!venc)
		return -ENOMEM;

	venc->pdev = pdev;
	venc->dss = dss;
	dev_set_drvdata(dev, venc);

	/* The OMAP34xx, OMAP35xx and AM35xx VENC require the TV DAC clock. */
	if (soc_device_match(venc_soc_devices))
		venc->requires_tv_dac_clk = true;

	mutex_init(&venc->venc_lock);

	venc->wss_data = 0;

	venc_mem = platform_get_resource(venc->pdev, IORESOURCE_MEM, 0);
	venc->base = devm_ioremap_resource(&pdev->dev, venc_mem);
	if (IS_ERR(venc->base)) {
		r = PTR_ERR(venc->base);
		goto err_free;
	}

	r = venc_get_clocks(venc);
	if (r)
		goto err_free;

	pm_runtime_enable(&pdev->dev);

	r = venc_runtime_get(venc);
	if (r)
		goto err_runtime_get;

	rev_id = (u8)(venc_read_reg(venc, VENC_REV_ID) & 0xff);
	dev_dbg(&pdev->dev, "OMAP VENC rev %d\n", rev_id);

	venc_runtime_put(venc);

	r = venc_probe_of(venc);
	if (r) {
		DSSERR("Invalid DT data\n");
		goto err_probe_of;
	}

	venc->debugfs = dss_debugfs_create_file(dss, "venc", venc_dump_regs,
						venc);

	venc_init_output(venc);

	return 0;

err_probe_of:
err_runtime_get:
	pm_runtime_disable(&pdev->dev);
err_free:
	kfree(venc);
	return r;
}
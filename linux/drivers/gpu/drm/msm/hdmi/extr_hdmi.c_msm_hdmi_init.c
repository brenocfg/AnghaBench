#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct regulator {int dummy; } ;
struct TYPE_8__ {struct hdmi_platform_config* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hdmi_platform_config {int hpd_reg_cnt; int pwr_reg_cnt; int hpd_clk_cnt; int pwr_clk_cnt; int /*<<< orphan*/ * pwr_clk_names; int /*<<< orphan*/ * hpd_clk_names; int /*<<< orphan*/ * pwr_reg_names; int /*<<< orphan*/ * hpd_reg_names; int /*<<< orphan*/  qfprom_mmio_name; int /*<<< orphan*/  mmio_name; } ;
struct hdmi {struct regulator* hdcp_ctrl; struct regulator* i2c; int /*<<< orphan*/  workq; struct regulator** pwr_clks; struct regulator** hpd_clks; struct regulator** pwr_regs; struct regulator** hpd_regs; struct regulator* qfprom_mmio; int /*<<< orphan*/  mmio_phy_addr; struct regulator* mmio; int /*<<< orphan*/  reg_lock; struct hdmi_platform_config* config; struct platform_device* pdev; } ;
typedef  struct regulator clk ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (TYPE_1__*,char*) ; 
 int ENOMEM ; 
 struct hdmi* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 void* devm_kcalloc (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 struct hdmi* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator* devm_regulator_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct regulator* msm_clk_get (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_hdmi_destroy (struct hdmi*) ; 
 int msm_hdmi_get_phy (struct hdmi*) ; 
 struct regulator* msm_hdmi_hdcp_init (struct hdmi*) ; 
 struct regulator* msm_hdmi_i2c_init (struct hdmi*) ; 
 void* msm_ioremap (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hdmi *msm_hdmi_init(struct platform_device *pdev)
{
	struct hdmi_platform_config *config = pdev->dev.platform_data;
	struct hdmi *hdmi = NULL;
	struct resource *res;
	int i, ret;

	hdmi = devm_kzalloc(&pdev->dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi) {
		ret = -ENOMEM;
		goto fail;
	}

	hdmi->pdev = pdev;
	hdmi->config = config;
	spin_lock_init(&hdmi->reg_lock);

	hdmi->mmio = msm_ioremap(pdev, config->mmio_name, "HDMI");
	if (IS_ERR(hdmi->mmio)) {
		ret = PTR_ERR(hdmi->mmio);
		goto fail;
	}

	/* HDCP needs physical address of hdmi register */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
		config->mmio_name);
	hdmi->mmio_phy_addr = res->start;

	hdmi->qfprom_mmio = msm_ioremap(pdev,
		config->qfprom_mmio_name, "HDMI_QFPROM");
	if (IS_ERR(hdmi->qfprom_mmio)) {
		DRM_DEV_INFO(&pdev->dev, "can't find qfprom resource\n");
		hdmi->qfprom_mmio = NULL;
	}

	hdmi->hpd_regs = devm_kcalloc(&pdev->dev,
				      config->hpd_reg_cnt,
				      sizeof(hdmi->hpd_regs[0]),
				      GFP_KERNEL);
	if (!hdmi->hpd_regs) {
		ret = -ENOMEM;
		goto fail;
	}
	for (i = 0; i < config->hpd_reg_cnt; i++) {
		struct regulator *reg;

		reg = devm_regulator_get(&pdev->dev,
				config->hpd_reg_names[i]);
		if (IS_ERR(reg)) {
			ret = PTR_ERR(reg);
			DRM_DEV_ERROR(&pdev->dev, "failed to get hpd regulator: %s (%d)\n",
					config->hpd_reg_names[i], ret);
			goto fail;
		}

		hdmi->hpd_regs[i] = reg;
	}

	hdmi->pwr_regs = devm_kcalloc(&pdev->dev,
				      config->pwr_reg_cnt,
				      sizeof(hdmi->pwr_regs[0]),
				      GFP_KERNEL);
	if (!hdmi->pwr_regs) {
		ret = -ENOMEM;
		goto fail;
	}
	for (i = 0; i < config->pwr_reg_cnt; i++) {
		struct regulator *reg;

		reg = devm_regulator_get(&pdev->dev,
				config->pwr_reg_names[i]);
		if (IS_ERR(reg)) {
			ret = PTR_ERR(reg);
			DRM_DEV_ERROR(&pdev->dev, "failed to get pwr regulator: %s (%d)\n",
					config->pwr_reg_names[i], ret);
			goto fail;
		}

		hdmi->pwr_regs[i] = reg;
	}

	hdmi->hpd_clks = devm_kcalloc(&pdev->dev,
				      config->hpd_clk_cnt,
				      sizeof(hdmi->hpd_clks[0]),
				      GFP_KERNEL);
	if (!hdmi->hpd_clks) {
		ret = -ENOMEM;
		goto fail;
	}
	for (i = 0; i < config->hpd_clk_cnt; i++) {
		struct clk *clk;

		clk = msm_clk_get(pdev, config->hpd_clk_names[i]);
		if (IS_ERR(clk)) {
			ret = PTR_ERR(clk);
			DRM_DEV_ERROR(&pdev->dev, "failed to get hpd clk: %s (%d)\n",
					config->hpd_clk_names[i], ret);
			goto fail;
		}

		hdmi->hpd_clks[i] = clk;
	}

	hdmi->pwr_clks = devm_kcalloc(&pdev->dev,
				      config->pwr_clk_cnt,
				      sizeof(hdmi->pwr_clks[0]),
				      GFP_KERNEL);
	if (!hdmi->pwr_clks) {
		ret = -ENOMEM;
		goto fail;
	}
	for (i = 0; i < config->pwr_clk_cnt; i++) {
		struct clk *clk;

		clk = msm_clk_get(pdev, config->pwr_clk_names[i]);
		if (IS_ERR(clk)) {
			ret = PTR_ERR(clk);
			DRM_DEV_ERROR(&pdev->dev, "failed to get pwr clk: %s (%d)\n",
					config->pwr_clk_names[i], ret);
			goto fail;
		}

		hdmi->pwr_clks[i] = clk;
	}

	pm_runtime_enable(&pdev->dev);

	hdmi->workq = alloc_ordered_workqueue("msm_hdmi", 0);

	hdmi->i2c = msm_hdmi_i2c_init(hdmi);
	if (IS_ERR(hdmi->i2c)) {
		ret = PTR_ERR(hdmi->i2c);
		DRM_DEV_ERROR(&pdev->dev, "failed to get i2c: %d\n", ret);
		hdmi->i2c = NULL;
		goto fail;
	}

	ret = msm_hdmi_get_phy(hdmi);
	if (ret) {
		DRM_DEV_ERROR(&pdev->dev, "failed to get phy\n");
		goto fail;
	}

	hdmi->hdcp_ctrl = msm_hdmi_hdcp_init(hdmi);
	if (IS_ERR(hdmi->hdcp_ctrl)) {
		dev_warn(&pdev->dev, "failed to init hdcp: disabled\n");
		hdmi->hdcp_ctrl = NULL;
	}

	return hdmi;

fail:
	if (hdmi)
		msm_hdmi_destroy(hdmi);

	return ERR_PTR(ret);
}